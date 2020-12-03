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
    void addFile(const std::string parentName, const int parentId, File file);
    static int getNewId();
    Folder* targetDir(Folder *currentFolder, std::string destinationName);
};

Folder* findFolder(std::vector<Folder *>, const std::string, const int id);
Folder* findFolder(std::vector<Folder *>, const std::string);
Folder* findParent(std::vector<Folder *> folders, const std::string parentName, int childId);
void strToVector(std::string line, std::vector<std::string> *words, std::string seperator);

#endif