#include "treemodel.h"
#include <treeitem.h>

TreeModel::TreeModel(LibQGit2::Repository const* repository, QObject *parent)
    : QAbstractItemModel(parent)
{
    setupModelData(repository);
}

TreeModel::~TreeModel()
{
    delete _rootItem;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
            return QModelIndex();

    TreeItem *parentItem = getItem(parent);

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();

}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem ==_rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem = getItem(parent);
    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return _rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item->data(role - AuthorRole);
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return _rootItem->data(section);

    return QVariant();
}

void TreeModel::setupModelData(LibQGit2::Repository const* _repository) {

    emit beginResetModel();
    if(_rootItem)
    {
        //delete everything
    }

    _rootItem = new TreeItem();
    TreeItem* parent = _rootItem;

    LibQGit2::RevWalk rev(*_repository);

    QStringList branches = _repository->listReferences();

    for(auto const& branch : branches) {
        rev.push(_repository->lookupRefOId(branch));
        LibQGit2::Commit c;
        while(rev.next(c)) {
            auto child = new TreeItem(c, parent);
            parent->appendChild(child);
            parent = child;
        }
        break;
    }
    emit endResetModel();
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return _rootItem;
}

QHash<int, QByteArray> TreeModel::roleNames() const {
    QHash<int, QByteArray> roles;
      roles[AuthorRole] = "author";
      roles[MessageRole] = "message";
    return roles;
}
