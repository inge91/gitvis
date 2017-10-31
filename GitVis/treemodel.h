#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QObject>
#include <QModelIndex>
#include <qgit2/qgitrevwalk.h>

class TreeItem;
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(QString test READ test CONSTANT)


public:
    enum CommitRoles {
          AuthorRole = Qt::UserRole + 1,
          MessageRole
      };

    QString test() {
        QModelIndex i = index(0,0);
        return i.data(0).toString();
    }

    TreeModel(LibQGit2::Repository const* repository, QObject *parent = 0);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    TreeItem* getItem(const QModelIndex &index) const;

public slots:
    void setupModelData(LibQGit2::Repository const* _repository);

private:
    TreeItem *_rootItem = nullptr;
};

#endif // TREEMODEL_H
