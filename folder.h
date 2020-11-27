#ifndef FOLDER
#define FOLDER

#include <iostream>
#include <vector>

class Folder
{
private:
    int id;
    std::string name;
    std::vector<Folder*> fileSystem;
    static int latestId;
public:
    Folder();
    Folder(const std::string&);
    Folder(const std::string&, const int&);
    Folder(const int&, const std::vector<Folder*>&);
    Folder(const std::string&, const std::vector<Folder*>&);
    Folder(const std::string&, const int&, const std::vector<Folder*>&);
    ~Folder();
    static Folder* findFolder(Folder&, const int&);
    static Folder* findFolder(Folder&, const std::string&);
    static Folder* findFolder(Folder&, const std::string&, const int&);
    static int getNewId();
    std::vector<Folder*> getFileSystem();
    std::string getName();
    std::string getSubfoldersString();
    int getId();
    void setName(const std::string&);
    void setId(const int&);
    void setFileSystem(const std::vector<Folder*>&);
    void addFolder(const std::vector<Folder*>&);
    void addFolder(Folder*);
};

#endif
