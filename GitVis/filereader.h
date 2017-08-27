#ifndef FILEREADER_H
#define FILEREADER_H

#include <qstring.h>
#include <qobject.h>
#include <qgit2/qgitrepository.h>
#include <qgit2/qgitrevwalk.h>
#include <git2.h>
#include <experimental/optional>
#include <iostream>

class FileReader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString gitFolder READ getGitFolder WRITE setGitFolder NOTIFY gitFolderChanged)
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
        _repository = new LibQGit2::Repository(repo, true);
        emit gitFolderChanged();
        gitRevWalk();
    }

    void gitRevWalk() {
        LibQGit2::RevWalk rev(*_repository);
        std::cout<< _repository->head().name().toStdString() <<std::endl;
        git_commit* commit;

        git_commit_lookup(&commit, _repository->data(), _repository->head().target().data());
        LibQGit2::Commit c(commit);
        rev.push(_repository->head().target());
        LibQGit2::OId
        rev.next()
        while() {

        }
    }


signals:
    void gitFolderChanged();

private:
    LibQGit2::Repository* _repository = nullptr;
};

#endif // FILEREADER_H
