#include <iostream>
#include <vector>

#include "folder.h"
#include "filePlan.h"


int FilePlan::latestId = 0;

int main()
{
    Folder root("/");
    root.setId(0);
    Folder home("home");
    Folder user1("user1");

    Folder desktop("desktop");
    Folder documents("documents");
    Folder downloads("downloads");
    Folder music("music");
    Folder pictures("pictures");
    Folder videos("videos");

    FilePlan filePlan(root);

    filePlan.addFolderToPlan(root.getName(), root.getId(), &home);
    filePlan.addFolderToPlan(home.getName(), home.getId(), &user1);

    std::vector<Folder> user1Children;

    user1Children = {desktop, documents, downloads, music, pictures, videos};
    filePlan.addFolderToPlan(user1.getName(), user1.getId(), &user1Children);

    Folder current = findFolder(filePlan.getSystemFile(), user1.getName(), user1.getId());
    std::cout << current.getChildren().size() << std::endl;
}