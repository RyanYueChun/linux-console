#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>

#include "folder.h"
#include "file.h"
#include "filePlan.h"


int FilePlan::latestId = 0;

FilePlan* fetchFilePlan(std::vector<FilePlan *> listFilePlans, std::string fpName)
{
    for (FilePlan *fp : listFilePlans)
    {
        if (fpName == fp->getName())
        {
            return fp;
        }
    }
    return new FilePlan(NOT_FOUND);
}

void secureCopy(File fileToSend, Folder *destFolder)
{
    destFolder->addFile(fileToSend);
}

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
    filePlan.setName("Local");

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

    // -------------
    // Remote systyme file accessible using ssh
    Folder rRoot("/");
    rRoot.setId(0);
    rRoot.setPath(rRoot.getName());
    Folder rHome("home");
    Folder remoteUser("remoteUser");

    Folder rDesktop("desktop");
    Folder rDocuments("documents");
    Folder rDownloads("downloads");
    Folder rMusic("music");
    Folder rPictures("pictures");
    Folder rVideos("videos");

    FilePlan remoteSystem(&rRoot);
    remoteSystem.setName("Remote");

    remoteSystem.addFolderToPlan(rRoot.getName(), rRoot.getId(), &rHome);
    remoteSystem.addFolderToPlan(rHome.getName(), rHome.getId(), &remoteUser);

    std::vector<Folder *> remoteUserChildren;
    remoteUserChildren = {
        &rDesktop,
        &rDocuments,
        &rDownloads,
        &rMusic,
        &rPictures,
        &rVideos
    };

    remoteSystem.addFolderToPlan(remoteUser.getName(), remoteUser.getId(), remoteUserChildren);
    // -------------

    // Folder where console is by default
    Folder *selectedFolder = findFolder(filePlan.getSystemFile(), user1.getName(), user1.getId());
    std::cout << selectedFolder->getPath() << std::endl;

    // Current File system that the console is using
    // FilePlan selectedFilePlan("temp");
    // selectedFilePlan = filePlan;
    FilePlan *pSelectedFP = &filePlan;

    std::vector<FilePlan *> listFilePlans = {&filePlan, &remoteSystem};

    // -----------------
    // Program begin
    // Read user's input
    std::string line;
    std::vector<Folder *> createdFolders;
    std::vector<std::string> createdFiles;
    std::string storageFolder = "contents/";
    while(line != "quit")
    {
        std::vector<std::string> words;
        
        std::getline(std::cin, line);

        strToVector(line, &words, " ");

        if (words[0] == "cd" && words.size() == 2)
        {
            // cd has only 1 argument
            selectedFolder = pSelectedFP->targetDir(selectedFolder, words[1]);
        }
        if (words[0] == "ls")
        {
            Folder *temp;
            if (words.size() == 2)
            {
                temp = pSelectedFP->targetDir(selectedFolder, words[1]);
                std::cout << temp->listOfChildren() + "\t\t" + temp->listOfFiles() << std::endl;
                std::cout << selectedFolder->getName() + "\n";
            } else
            {
                std::cout << selectedFolder->listOfChildren() + "\t\t" + selectedFolder->listOfFiles() << std::endl;
            }
        }
        if (words[0] == "mkdir")
        {
            for (int i = 1; i < words.size(); i++)
            {
                Folder *createdFolder = new Folder(words[i]);
                pSelectedFP->addFolderToPlan(selectedFolder->getName(), selectedFolder->getId(), createdFolder);
                createdFolders.push_back(createdFolder);
            }
        }
        if (words[0] == "vi")
        {
            if (words.size() == 2 && !words[1].empty())
            {
                std::ifstream fileInput(storageFolder + words[1], std::ios::in);
                std::ofstream fileOutput(storageFolder + words[1], std::ios_base::app);
                std::string text;
                if (fileOutput.is_open())
                {
                    File createdFile(words[1]);
                    pSelectedFP->addFile(selectedFolder->getName(), selectedFolder->getId(), createdFile);
                    if (fileInput.is_open())
                    {
                        while (getline(fileInput, text))
                        {
                            std::cout << text << std::endl;
                        }
                    }
                    getline(std::cin, text);
                    fileOutput << text << std::endl;
                    std::cout << "Text saved\n";
                    createdFiles.push_back(words[1]);
                }
            } else
            {
                std::cout << "Amount of arguments inadequate\n";
            }
            
        }
        if (words[0] == "ssh")
        {
            if (words.size() == 2 && !words[1].empty())
            {
                pSelectedFP = fetchFilePlan(listFilePlans, words[1]);
                selectedFolder = findFolder(pSelectedFP->getSystemFile(), pSelectedFP->getSystemFile()[2]->getName(), pSelectedFP->getSystemFile()[2]->getId());
            } else
            {
                std::cout << "Amount of arguments inadequate\n";
            }
        }
        if (words[0] == "exit")
        {
            if (pSelectedFP != &filePlan)
            {
                pSelectedFP = &filePlan;
                selectedFolder = findFolder(filePlan.getSystemFile(), user1.getName(), user1.getId());
            }
        }
        if (words[0] == "scp" && words.size() == 3)
        {
            std::vector<std::string> sepColumn;
            std::vector<std::string> sepSlash;
            strToVector(words[2], &sepColumn, ":");

            File fileToSend = selectedFolder->fetchFile(words[1]);
            Folder destFolder("/");
            Folder *pDestFolder = &destFolder;
            FilePlan *destFilePlan = fetchFilePlan(listFilePlans, sepColumn[0]);

            if (sepColumn.size() > 1)
            {
                strToVector(sepColumn[1], &sepSlash, "/");

                std::cout << "rrrrrrrrrrrrrr\n";

                fileToSend.setName(sepSlash.back());
                sepSlash.pop_back();

                std::cout << "rrrrrrrrrrrrrr\n";

                if (sepSlash.size() > 0)
                {
                    pDestFolder = destFilePlan->targetDir(pDestFolder, sepSlash);
                } else
                {
                    pDestFolder = destFilePlan->getSystemFile()[2];
                }
            } else
            {
                pDestFolder = destFilePlan->getSystemFile()[2];
            }
            
            secureCopy(fileToSend, pDestFolder);
        } else if (words[0] == "scp" && words.size() != 3)
        {
            std::cout << "Amount of arguments inadequate\n";
        }
        std::cout << selectedFolder->getPath() + " $ ";
    }
    std::cout << std::endl;
    // Program end
    // -----------------

    for (std::vector<Folder *>::iterator i = createdFolders.begin(); i != createdFolders.end(); ++i)
    {
        delete *i;
    }
    createdFolders.clear();
    if (selectedFolder->getName() == NOT_FOUND)
    {
        delete selectedFolder;
    }
    for (std::string file : createdFiles)
    {
        std::string fName = storageFolder + file;
        std::ifstream fileInput(fName, std::ios::in);
        if (fileInput.is_open())
        {
            // delete created files
            const int result = remove(fName.c_str());
        }
    }
}