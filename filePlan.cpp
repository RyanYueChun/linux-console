#include <iostream>
#include "filePlan.h"

FilePlan::FilePlan(std::string name)
{
    this->name = name;
}

FilePlan::FilePlan(Folder *root)
{
    this->systemFile.push_back(root);
}

std::vector<Folder *> FilePlan::getSystemFile()
{
    return this->systemFile;
}

std::string FilePlan::getName()
{
    return this->name;
}
void FilePlan::setName(std::string name)
{
    this->name = name;
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
    if(parent->getName() != NOT_FOUND)
    {
        // child already exist?
        Folder *found = findFolder(parent->getChildren(), newChildFolder->getName());
        if(found->getName() != NOT_FOUND)
        {
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
    newChildFolder->setPath(currentFolder->getPath() + newChildFolder->getName() + "/");
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

void FilePlan::addFile(const std::string parentName, const int parentId, File file)
{
    std::vector<Folder *> folders = this->systemFile;

    Folder *parent = findFolder(folders, parentName, parentId);
    if(parent->getName() != NOT_FOUND)
    {
        // file already exist?
        std::string found = parent->fetchFile(file.getName());
        if(found != NOT_FOUND)
        {
            std::cout << "File \'" + file.getName() + "\' already exists inside " << parent->getName() + ". Entering edit mode" << std::endl;
        } else
        {
            parent->addFile(file);
            std::cout << "File \'" + file.getName() + "\' created inside " << parent->getName() << std::endl;
        }
    } else
    {
        std::cout << "The parent folder doesn't exist\n";
        // Object created in the "heap" with "new" operator must be deleted manually
        delete parent;
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
            if (folder->getName() == name && folder->getId() == id)
            {
                return folder;
            }
        }
    }
    return new Folder(NOT_FOUND);
}

Folder* findFolder(std::vector<Folder *> folders, const std::string name)
{
    if(!folders.empty())
    {
        for(Folder *folder : folders)
        {
            if (folder->getName() == name)
            {
                return folder;
            }
        }
    }
    return new Folder(NOT_FOUND);
}

Folder* findParent(std::vector<Folder *> folders, const std::string parentName, int childId)
{
    std::vector<Folder*> foundNames;

    if(!folders.empty())
    {
        for(Folder *folder : folders)
        {
            if (folder->getName() == parentName)
            {
                for (Folder *child : folder->getChildren())
                {
                    if (child->getId() == childId)
                    {
                        return folder;
                    }
                }
            }
        }
    }
    return new Folder(NOT_FOUND);
}

void strToVector(std::string line, std::vector<std::string> *words, std::string seperator)
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

Folder* FilePlan::targetDir(Folder *currentFolder, std::string fullDestinationName)
{
    std::vector<std::string> args;
    strToVector(fullDestinationName, &args, "/");

    if (fullDestinationName[0] == '/')
    {
        currentFolder = findFolder(this->getSystemFile(), "/", 0);
    }
    return targetDir(currentFolder, args);
}

Folder* FilePlan::targetDir(Folder *currentFolder, std::vector<std::string> noSlashDestVect)
{
    for (std::string arg : noSlashDestVect)
    {
        if (arg == ".")
        {
            continue;
        }
        if (arg == "..")
        {
            std::vector<std::string> parentNames;
            strToVector(currentFolder->getPath(), &parentNames, "/");
            currentFolder = findParent(this->getSystemFile(), parentNames[parentNames.size() - 2], currentFolder->getId());
            continue;
        }

        Folder *found = findFolder(currentFolder->getChildren(), arg);
        if (found->getName() == NOT_FOUND)
        {
            std::cout << arg + " not found in " + currentFolder->getName() << std::endl;
            delete found;
            break;
        }
        currentFolder = found;
    }
    return currentFolder;
}