#ifndef FOLDER
#define FOLDER

#include <string>
#include <vector>
#include "file.h"

class Folder
{
private:
    int id;
    std::string name;
    std::string path;
    std::vector<Folder *> children;
    std::vector<File> contents;
public:
    Folder();
    Folder(const std::string name);
    Folder(const std::string, const int, const std::vector<Folder *>);

    int getId();
    void setId(int);

    std::string getName();
    void setName(std::string);

    std::string getPath();
    void setPath(std::string);

    std::vector<Folder *> getChildren();
    void setChildren(std::vector<Folder *>);

    void addChild(Folder *);
    void addChildren(std::vector<Folder *>);
    std::string listOfChildren();
    
    std::vector<File> getContents();
    void addContent(File content);
    std::string listOfContents();
};

template <typename T>
std::string printVector(std::vector<T> vector);

#endif