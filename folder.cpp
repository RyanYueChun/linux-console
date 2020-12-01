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
    std::vector<Folder *> list = this->getChildren();
    std::string strList;
    for(Folder *f : list)
    {
        strList += (*f).getName() + "\t";
    }
    return strList;
}