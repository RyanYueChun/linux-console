#include <iostream>
#include <vector>

#include "folder.h"

int Folder::latestId = 0;

int main()
{
    Folder root("/");
    Folder home("home");
    Folder user1("user1");

    Folder desktop("desktop");
    Folder documents("documents");
    Folder downloads("downloads");
    Folder music("music");
    Folder pictures("pictures");
    Folder videos("videos");

    root.addFolder(&home);
    home.addFolder(&user1);

    std::vector<Folder*> user1Children = {&desktop, &documents, &downloads, &music, &pictures, &videos, &videos};
    user1.addFolder(user1Children);

    Folder* current = Folder::findFolder(root,home.getId());
    std::cout << "\'current\' size: " << current->getFileSystem().size() << std::endl;
    std::cout << "\'user1\' files: \n" << user1.getSubfoldersString() << std::endl;
}
