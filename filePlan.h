#ifndef FILE_PLAN
#define FILE_PLAN

#include "folder.h"

class FilePlan
{
private:
    std::vector<Folder *> systemFile;
    static int latestId;
public:
    FilePlan(Folder *);
    std::vector<Folder *> getSystemFile();
    void addFolderToPlan(const std::string parentName, const int parentId, std::vector<Folder *> newChildrenFolders);
    void addFolderToPlan(const std::string parentName, const int parentId, Folder * newChildFolder);
    void addAsChild(Folder *, Folder *);
    void addAsChild(Folder *, std::vector<Folder *>);
    static int getNewId();
};

Folder* findFolder(std::vector<Folder *>, const std::string, const int id);
Folder* findFolder(std::vector<Folder *>, const std::string);
void readCommand(std::string line, std::vector<std::string> *words, std::string seperator);


#endif