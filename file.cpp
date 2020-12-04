#include "file.h"

File::File(std::string name)
{
    this->name = name;
}

void File::setName(std::string name)
{
    this->name = name;
}

std::string File::getName()
{
    return this->name;
}

std::string File::getContent()
{
    return this->content;
}

void File::setContent(std::string content)
{
    this->content;
}