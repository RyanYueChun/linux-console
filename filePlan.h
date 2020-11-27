#ifndef FILE_PLAN
#define FILE_PLAN

#include "folder.h"

class FilePlan
{
private:
    std::vector<Folder> systemFile;
    static int latestId;
public:
    FilePlan(Folder);
    std::vector<Folder> getSystemFile();
    void addFolderToPlan(std::string parentName, int parentLevel, std::vector<Folder> *newChildrenFolders);
    void addFolderToPlan(std::string parentName, int parentLevel, Folder *newChildFolder);
    void addAsChild(Folder*, Folder*);
    void addAsChild(Folder*, std::vector<Folder>*);
    static int getNewId();
};

Folder findFolder(std::vector<Folder>, std::string, int id);
Folder findFolder(std::vector<Folder>, std::string);

#endif