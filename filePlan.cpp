#include <iostream>
#include "filePlan.h"

FilePlan::FilePlan(Folder *root)
{
    this->systemFile.push_back(root);
}

std::vector<Folder *> FilePlan::getSystemFile()
{
    return this->systemFile;
}

void FilePlan::addFolderToPlan(std::string parentName, int parentId, std::vector<Folder *> newChildrenFolders)
{
    for(Folder *child : newChildrenFolders)
    {
        addFolderToPlan(parentName, parentId, child);
    }
}

void FilePlan::addFolderToPlan(const std::string parentName, const int parentId, Folder *newChildFolder)
{
    std::vector<Folder *> folders = this->systemFile;

    Folder *parent = findFolder(folders, parentName, parentId);
    if(parent->getName() != "Not Found")
    {
        // child already exist?
        Folder *found = findFolder(parent->getChildren(), newChildFolder->getName());
        if(found->getName() != "Not Found")
        {
            std::cout << parent->getName() + " : " + parentName << "\n";
            std::cout << "Folder \'" + (*newChildFolder).getName() + "\' already exists inside " << parent->getName() << std::endl;
        } else
        {
            addAsChild(parent, newChildFolder);
            std::cout << "Folder \'" + (*newChildFolder).getName() + "\' created inside " << parent->getName() << std::endl;
            // Object created in the "heap" with "new" operator must be deleted manually
            delete found;
        }
    } else
    {
        std::cout << "The parent folder doesn't exist\n";
        // Object created in the "heap" with "new" operator must be deleted manually
        delete parent;
    }
}

void FilePlan::addAsChild(Folder *currentFolder, Folder *newChildFolder)
{
    newChildFolder->setId(getNewId());
    currentFolder->addChild(newChildFolder);
    this->systemFile.push_back(newChildFolder);
}

void FilePlan::addAsChild(Folder *currentFolder, std::vector<Folder *> newChildrenFolders)
{
    for(Folder *child : newChildrenFolders)
    {
        addAsChild(currentFolder, child);
    }
}

int FilePlan::getNewId()
{
    return ++FilePlan::latestId;
}

Folder* findFolder(std::vector<Folder *> folders, const std::string name, const int id)
{
    if(!folders.empty())
    {
        for(Folder *folder : folders)
        {
            if ((*folder).getName() == name && (*folder).getId() == id)
            {
                return folder;
            }
        }
    }
    return new Folder("Not Found");
}

Folder* findFolder(std::vector<Folder *> folders, const std::string name)
{
    if(!folders.empty())
    {
        for(Folder *folder : folders)
        {
            if ((*folder).getName() == name)
            {
                return folder;
            }
        }
    }
    return new Folder("Not Found");
}

void readCommand(std::string line, std::vector<std::string> *words, std::string seperator)
{
    while (line.size() > 0)
    {
        int i, j;
        i = line.find_first_not_of(seperator);

        if (i != std::string::npos)
        {
            j = line.find(seperator, i);

            if (j == std::string::npos)
            {
                words->push_back(line.substr(i));
                break;
            }
            words->push_back(line.substr(i, j-i));
            line = line.substr(j);
        } else
        {
            break;
        }
    }
}