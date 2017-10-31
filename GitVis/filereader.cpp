#include "filereader.h"

FileReader::FileReader()
{
    setGitFolder("/home/inge/Projects/test");
    //connect(this, &FileReader::gitFolderChanged, _treeModel, &TreeModel::setupModelData);
    //connect(&_treeModel, &TreeModel::treeModelChanged, this, &FileReader::treeModelChanged);
}
