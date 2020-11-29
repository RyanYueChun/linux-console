#ifndef FOLDER
#define FOLDER

#include <string>
#include <vector>

class Folder
{
private:
    int id;
    std::string name;
    std::string path;
    std::vector<Folder *> children;
public:
    Folder();
    Folder(const std::string name);
    Folder(const std::string, const int, const std::vector<Folder *>);
    std::string getName();
    std::string getPath();
    int getId();
    std::vector<Folder *> getChildren();
    void setName(std::string);
    void setPath(std::string);
    void setId(int);
    void setChildren(std::vector<Folder *>);
    void addChild(Folder *);
    void addChildren(std::vector<Folder *>);
    std::string listOfChildren();
};

#endif