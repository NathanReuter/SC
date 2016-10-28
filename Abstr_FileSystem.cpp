/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileSystem.cpp
 * Author: cancian
 * 
 * Created on 29 de Agosto de 2016, 14:56
 */

#include <iostream>
#include "Abstr_FileSystem.h"
#include "OperatingSystem.h"
#include <string.h>

FileSystem::FileSystem() {
    fileAllocator = new FileAllocator(OperatingSystem::HardDisk_Mediator(),
                                      new FileAllocationTable(OperatingSystem::HardDisk_Mediator()));
    rootDirectory = new Directory("/");

//    TESTE CODE

    rootDirectory->addDirEntry(DirectoryEntry("foo", 1, DirectoryEntry::entryType::DIRECTORY));
    rootDirectory->addDirEntry(DirectoryEntry("bar.c", 2, DirectoryEntry::entryType::FILE));
}


FileSystem::~FileSystem() {
}

void FileSystem::list(const char *path) {
    std::list<const char*> list = rootDirectory->listContent();
//    USE getPathDirectory
    std::cout << "Listing Directory: " << path << std::endl;
    for (std::list<const char*>::iterator name = list.begin(); name != list.end(); name++) {
        std::cout << *name << std::endl;
    }
}

int FileSystem::createFile() {
    fileAllocator->createFile("/");
    return 0;
}

std::list<const char *> FileSystem::splitPath(const char *path) {
    const int maxPathLength = 255; //Just for test
    char temp[maxPathLength];
    std::list<const char *> directories;

    if (strlen(path) > maxPathLength) {
        return null;
    }

    strncpy(temp,path,maxPathLength);
    char * pch;
    pch = strtok (temp,"/");

    while (pch != NULL) {
        directories.push_back(pch);
        pch = strtok (NULL, "/");
    }

    return directories;
}

Directory FileSystem::getPathDirectory(const char *path) {
    std::list<const char *> directories = splitPath(path);
    Directory * currentDir;
    for (std::list<const char*>::iterator name = directories.begin(); name != directories.end(); name++) {
        if (rootDirectory->contains(*name, Directory::SearchType::DIR)) {
//            FETCH from HD the directory from block
            HW_HardDisk::blockNumber number = rootDirectory->getEnty(*name).getBlockIndex();
//            Carregar o diretorio na variavel currentDIr
//            Depois se for o ultimo da lista retorna
            if (name == directories.end()) {
                return *currentDir;
            }
        }
        std::cout << *name << std::endl;
    }
}
