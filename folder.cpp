#include "folder.h"

Folder::Folder()
{}

Folder::Folder(const std::string name)
{
    this->setName(name);
    this->children = {};
}

// Folder::Folder(const std::string name, const int id, const std::vector<Folder *> children)
// {
//     this->setName(name);
//     this->setId(id);
//     this->setChildren(children);
// }

int Folder::getId()
{
    return this->id;
}
void Folder::setId(int id)
{
    this->id = id;
}

std::string Folder::getName()
{
    return this->name;
}
void Folder::setName(std::string name)
{
    this->name = name;
}

std::string Folder::getPath()
{
    return this->path;
}
void Folder::setPath(std::string path)
{
    this->path = path;
}

std::vector<Folder *> Folder::getChildren()
{
    return this->children;
}
void Folder::setChildren(std::vector<Folder *> children)
{
    this->children = children;
}

void Folder::addChild(Folder * child)
{
    this->children.push_back(child);
}
void Folder::addChildren(std::vector<Folder *> children)
{
    for(Folder *child : children)
    {
        addChild(child);
    }
}
std::string Folder::listOfChildren()
{
    std::vector<Folder *> vector = this->getChildren();
    std::string strList;
    for(Folder *f : vector)
    {
        strList += f->getName() + "\t";
    }
    return strList;
}

std::vector<File> Folder::getFiles()
{
    return this->files;
}
std::string Folder::fetchFile(std::string fileName)
{
    for (File file : this->getFiles())
    {
        if (file.getName() == fileName)
        {
            return file.getName();
        }
    }
    return NOT_FOUND;
}
void Folder::addFile(File content)
{
    this->files.push_back(content);
}
std::string Folder::listOfFiles()
{
    std::vector<File> vector = this->getFiles();
    std::string strList;
    for(File f : vector)
    {
        strList += f.getName() + "\t";
    }
    return strList;
}

template <typename T>
std::string printVector(std::vector<T> vector)
{
    std::string strList;
    for(T f : vector)
    {
        strList += f + "\t";
    }
    return strList;
}