#include <iostream>
#include "filePlan.h"

FilePlan::FilePlan(Folder root)
{
    this->systemFile.push_back(root);
}

std::vector<Folder> FilePlan::getSystemFile()
{
    return this->systemFile;
}

void FilePlan::addFolderToPlan(std::string parentName, int parentId, std::vector<Folder> *newChildrenFolders)
{
    for(Folder child : *newChildrenFolders)
    {
        addFolderToPlan(parentName, parentId, &child);
    }
}

void FilePlan::addFolderToPlan(std::string parentName, int parentId, Folder *newChildFolder)
{
    std::vector<Folder> folders = this->systemFile;
    Folder parent = findFolder(folders, parentName, parentId);

    if(parent.getName() == parentName)
    {
        // child already exist?
        if(findFolder(parent.getChildren(), (*newChildFolder).getName()).getName() == (*newChildFolder).getName())
        {
            std::cout << parent.getName() + " : " + parentName << "\n";
            std::cout << "Folder \'" + (*newChildFolder).getName() + "\' already exists inside " << parent.getName() << std::endl;
        } else
        {
            addAsChild(&parent, newChildFolder);
            std::cout << "Folder \'" + (*newChildFolder).getName() + "\' created inside " << parent.getName() << std::endl;
        }
    } else
    {
        std::cout << "The parent folder doesn't exist\n";
    }
}

void FilePlan::addAsChild(Folder *currentFolder, Folder *newChildFolder)
{
    (*newChildFolder).setId(getNewId());
    (*currentFolder).getChildren().push_back(*newChildFolder);
    this->systemFile.push_back(*newChildFolder);
}

void FilePlan::addAsChild(Folder *currentFolder, std::vector<Folder> *newChildrenFolders)
{
    for(Folder child : *newChildrenFolders)
    {
        addAsChild(currentFolder, &child);
    }
}

Folder findFolder(std::vector<Folder> folders, std::string name, int id)
{
    if(!folders.empty())
    {
        for(Folder folder : folders)
        {
            if (folder.getName() == name && folder.getId() == id)
            {
                return folder;
            }
        }
    }
    Folder emptyFolder("Not Found");
    return emptyFolder;
}

Folder findFolder(std::vector<Folder> folders, std::string name)
{
    if(!folders.empty())
    {
        for(Folder folder : folders)
        {
            if (folder.getName() == name)
            {
                return folder;
            }
        }
    }
    Folder emptyFolder("Not Found");
    return emptyFolder;
}

int FilePlan::getNewId()
{
    return ++FilePlan::latestId;
}