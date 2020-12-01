#include <iostream>
#include <vector>
#include <fstream>

#include "folder.h"
#include "file.h"
#include "filePlan.h"


int FilePlan::latestId = 0;

int main()
{
    Folder root("/");
    root.setId(0);
    root.setPath(root.getName());
    Folder home("home");
    Folder user1("user1");

    Folder desktop("desktop");
    Folder documents("documents");
    Folder downloads("downloads");
    Folder music("music");
    Folder pictures("pictures");
    Folder videos("videos");

    FilePlan filePlan(&root);

    filePlan.addFolderToPlan(root.getName(), root.getId(), &home);
    filePlan.addFolderToPlan(home.getName(), home.getId(), &user1);

    std::vector<Folder *> user1Children;
    user1Children = {
        &desktop,
        &documents,
        &downloads,
        &music,
        &pictures,
        &videos
    };

    filePlan.addFolderToPlan(user1.getName(), user1.getId(), user1Children);

    // Folder where console is by default
    Folder *selectedFolder = findFolder(filePlan.getSystemFile(), music.getName(), music.getId());
    std::cout << selectedFolder->getPath() << std::endl;

    // Read user's input
    std::string line;
    std::vector<Folder *> createdFolders;
    std::string storageFolder = "contents/";
    while(line != "quit")
    {
        std::vector<std::string> words;
        
        std::getline(std::cin, line);

        strToVector(line, &words, " ");

        if (words[0] == "cd" && words.size() > 1)
        {
            // cd has only 1 argument
            selectedFolder = filePlan.targetDir(filePlan, selectedFolder, words[1]);
        }
        if (words[0] == "ls")
        {
            std::cout << selectedFolder->listOfChildren() << std::endl;
        }
        if (words[0] == "mkdir")
        {
            for (int i = 1; i < words.size(); i++)
            {
                Folder *createdFolder = new Folder(words[i]);
                filePlan.addFolderToPlan(selectedFolder->getName(), selectedFolder->getId(), createdFolder);
                createdFolders.push_back(createdFolder);
            }
        }
        if (words[0] == "vi")
        {
            std::ifstream fileInput(storageFolder + words[1], std::ios::in);
            std::ofstream fileOutput(storageFolder + words[1], std::ios_base::app);
            std::string text;
            if (fileInput.is_open())
            {
                while (getline(fileInput, text))
                {
                    std::cout << text << std::endl;
                }
            }
            if (fileOutput.is_open())
            {
                getline(std::cin, text);
                fileOutput << text << std::endl;
                std::cout << "Text saved\n";
            }
        }
        std::cout << selectedFolder->getPath() + " $ ";
    }
    std::cout << std::endl;

    for (std::vector<Folder *>::iterator i = createdFolders.begin(); i != createdFolders.end(); ++i)
    {
        delete *i;
    }
    createdFolders.clear();
    if (selectedFolder->getName() == NOT_FOUND)
    {
        delete selectedFolder;
    }
}