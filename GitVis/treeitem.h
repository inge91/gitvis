#ifndef TREEITEM_H
#define TREEITEM_H
#include <qstring.h>
#include <qgit2/qgitrepository.h>

class TreeItem
{
    enum dataValues{
        AUTHOR,
        MESSAGE
    };

public:
    TreeItem();
    explicit TreeItem(LibQGit2::Commit const& commit, TreeItem *parentItem = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem* parentItem();
    void setParent(TreeItem* parent);

private:
    QList<TreeItem*> _childItems;
    QMap<int, QString> _data;
    TreeItem *_parentItem = nullptr;
};

#endif // TREEITEM_H
