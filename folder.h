#ifndef FOLDER
#define FOLDER

#include <string>
#include <vector>

class Folder
{
private:
    int id;
    std::string name;
    std::vector<Folder> children;
public:
    Folder();
    Folder(std::string name);
    Folder(std::string, int, std::vector<Folder>);
    std::string getName();
    int getId();
    std::vector<Folder> getChildren();
    void setName(std::string);
    void setId(int);
    void setChildren(std::vector<Folder>&);
    std::string listOfChildren();
};

#endif