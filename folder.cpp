#include "folder.h"

Folder::Folder()
{}

Folder::Folder(std::string name)
{
    this->setName(name);
    this->children = {};
}

Folder::Folder(std::string name, int id, std::vector<Folder> children)
{
    this->setName(name);
    this->setId(id);
    this->setChildren(children);
}

std::string Folder::getName()
{
    return this->name;
}


int Folder::getId()
{
    return this->id;
}

std::vector<Folder> Folder::getChildren()
{
    return this->children;
}

void Folder::setName(std::string name)
{
    this->name = name;
}

void Folder::setId(int id)
{
    this->id = id;
}

void Folder::setChildren(std::vector<Folder> &children)
{
    this->children = children;
}

std::string Folder::listOfChildren()
{
    std::vector<Folder> list = this->getChildren();
    std::string strList;
    for(Folder f : list)
    {
        strList += f.getName() + "\t";
    }
    return strList;
}