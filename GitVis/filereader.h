#ifndef FILEREADER_H
#define FILEREADER_H

#include "treemodel.h"
#include <qstring.h>
#include <qobject.h>
#include <qgit2/qgitrepository.h>
#include <git2.h>
#include <experimental/optional>
#include <iostream>

class FileReader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString gitFolder READ getGitFolder WRITE setGitFolder NOTIFY gitFolderChanged)
    Q_PROPERTY(QObject* treeModel READ getTreeModel NOTIFY gitFolderChanged)

public:
    FileReader();

    ~FileReader(){
        delete _repository;
    }

    QString getGitFolder(){
        return _repository ? _repository->path() : "";
    }

    void setGitFolder(QString gitFolder) {
        git_repository *repo;
        git_repository_open(&repo, gitFolder.toStdString().c_str());
        if(repo == nullptr)
        {
            // TODO: Send warning back to qml
            return;
        }
        delete _repository;
        _repository = new LibQGit2::Repository(repo, true);
        emit gitFolderChanged();
    }

    QObject* getTreeModel() {
        delete _treeModel;
        _treeModel = new TreeModel(_repository);
        return _treeModel;
    }


signals:
    void gitFolderChanged();

private:
    TreeModel* _treeModel = nullptr;
    LibQGit2::Repository* _repository = nullptr;
};

#endif // FILEREADER_H
