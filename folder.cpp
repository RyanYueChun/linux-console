#include "folder.h"

Folder::Folder()
{
    this->name = "New Folder";
    this->id = getNewId();
}

Folder::Folder(const std::string& name)
{
    this->name = name;
    this->id = getNewId();
}

Folder::Folder(const std::string& name, const int& id)
{
    this->name = name;
    this->id = id;
}

Folder::Folder(const int& id, const std::vector<Folder*>& fileSystem)
{
    this->name = "New Folder";
    this->id = id;
    this->fileSystem = fileSystem;
}

Folder::Folder(const std::string& name, const std::vector<Folder*>& fileSystem)
{
    this->name = name;
    this->id = getNewId();
    this->fileSystem = fileSystem;
}

Folder* Folder::findFolder(Folder& searchPlace, const int& id)
{
    unsigned int length = searchPlace.fileSystem.size();
    for(unsigned int i = 0; i < length; i++)
        if(searchPlace.fileSystem[i]->id == id)
            return searchPlace.fileSystem[i];
    return nullptr;
}

Folder* Folder::findFolder(Folder& searchPlace, const std::string& name)
{
    unsigned int length = searchPlace.fileSystem.size();
    for(unsigned int i = 0; i < length; i++)
        if(searchPlace.fileSystem[i]->name == name)
            return searchPlace.fileSystem[i];
    return nullptr;
}

Folder* Folder::findFolder(Folder& searchPlace, const std::string& name, const int& id)
{
    unsigned int length = searchPlace.fileSystem.size();
    for(unsigned int i = 0; i < length; i++)
        if(searchPlace.fileSystem[i]->id == id && searchPlace.fileSystem[i]->name == name)
            return searchPlace.fileSystem[i];
    return nullptr;
}

Folder::~Folder()
{
    std::cout << "Destroyed " << this->name << " folder\n";
}

int Folder::getNewId()
{
    latestId++;
    return latestId;
}

std::vector<Folder*> Folder::getFileSystem()
{
    return this->fileSystem;
}

std::string Folder::getName()
{
    return this->name;
}

std::string Folder::getSubfoldersString()
{
    unsigned int length = this->fileSystem.size();
    std::string str;
    for(unsigned int i = 0; i < length; i++)
        str += this->fileSystem[i]->name + '\t';
    return str;
}

int Folder::getId()
{
    return this->id;
}

void Folder::setName(const std::string& name)
{
    this->name = name;
}

void Folder::setId(const int& id)
{
    this->id = id;
}

void Folder::setFileSystem(const std::vector<Folder*>& fileSystem)
{
    this->fileSystem = fileSystem;
}

void Folder::addFolder(const std::vector<Folder*>& folders)
{
    unsigned int length = folders.size();
    for(unsigned int i = 0; i < length; i++)
    {
        if(Folder::findFolder(*this,folders[i]->id) == nullptr)
        {
            fileSystem.push_back(folders[i]);
            std::cout << "Added " << folders[i]->name << " to " << this->name << ".\n";
        }
        else
        {
            std::cout << "\'" << folders[i]->name << "\' exists in this place!\n";
        }
    }
}

void Folder::addFolder(Folder* folder)
{
    if(Folder::findFolder(*this,folder->id) == nullptr)
    {
        fileSystem.push_back(folder);
        std::cout << "Added " << folder->name << " to " << this->name << ".\n";
    }
    else
    {
        std::cout << "\'" << folder->name << "\' exists in this place!\n";
    }
}
