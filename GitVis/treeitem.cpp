#include "treeitem.h"
#include <QVariant>

TreeItem::TreeItem()
{
    _data[MESSAGE] = "message";
    _data[AUTHOR] = "author";
}

TreeItem::TreeItem(LibQGit2::Commit const& commit, TreeItem *parent)
{
    _parentItem = parent;
    _data[MESSAGE] = commit.message();
    _data[AUTHOR] = commit.author().name();
    //_data["Data"] = commit;
}

TreeItem::~TreeItem()
{
    qDeleteAll(_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    _childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    return _childItems.value(row);
}

int TreeItem::childCount() const
{
    return _childItems.count();
}

int TreeItem::row() const
{
    if (_parentItem)
        return _parentItem->_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

int TreeItem::columnCount() const
{
    return _data.count();
}

QVariant TreeItem::data(int column) const
{
    return _data[column];
}

TreeItem *TreeItem::parentItem()
{
    return _parentItem;
}
