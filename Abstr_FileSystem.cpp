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

#define NO_FREE_BLOCKS_ERROR -1
#define NO_DIR_PATH_ERROR -2

FileSystem::FileSystem() {
    fileAllocator = new FileAllocator(OperatingSystem::HardDisk_Mediator(),
                                      new FileAllocationTable(OperatingSystem::HardDisk_Mediator()));
    rootDirectory = new Directory("/");
}


FileSystem::~FileSystem() {
}

void FileSystem::list(const char *path) {
    std::list<const char*> list = getPathDirectory(path)->listContent();
    std::cout << "Listing Directory: " << path << std::endl << std::endl;

    for (std::list<const char*>::iterator name = list.begin(); name != list.end(); name++) {
        std::cout << *name << std::endl;
    }
}

int FileSystem::createFile() {
//    fileAllocator->createFile();
    return 0;
}

std::list<const char *> FileSystem::splitPath(const char *path) {
    const int maxPathLength = 255; //Just for test
    char temp[maxPathLength];
    std::list<const char *> directories;

    if (strlen(path) > maxPathLength) {
        throw std::invalid_argument( "path length too big (255)" );
    }

    strncpy(temp,path,maxPathLength);
    char * pch;
    pch = strtok (temp,"/");

    if (pch == NULL) {
        pch = (char *)path;
    }

    while (pch != NULL) {
        directories.push_back(pch);
        pch = strtok (NULL, "/");
    }

    return directories;
}

/* Create an Directory in the given path
 * @param name {const char *}. Directory name
 * @param path {const char * path}. Path to be created
 * @return {int}. 0 on success, and -1 on error*/
int FileSystem::makeDir(const char *name, const char * path) {
    std::cout << "adsadasd" << std::endl;
    try {
        Directory * currentDir = getPathDirectory(path);

        if (fileAllocator->hasFreeBlocks() && !currentDir->contains(name, Directory::SearchType::DIRECTORY)) {
            std::cout << "MAKING DIR IN" << currentDir->getDirectoryName() << std::endl;
            HW_HardDisk::blockNumber block = fileAllocator->getNextFreeBlock();
//            block = fileAllocator->createFile();
            currentDir->addDirEntry(DirectoryEntry(name, block, DirectoryEntry::entryType::DIRECTORY));


            return 0;
        }

        return  NO_FREE_BLOCKS_ERROR;

    } catch (int e) {
        return  e;
    }
}

Directory * FileSystem::getPathDirectory(const char *path) {
    std::list<const char *> directories = splitPath(path);
    Directory * currentDir = rootDirectory;

    if (directories.size() > 1) {
        for (std::list<const char*>::iterator name = directories.begin(); name != directories.end(); name++) {

            if (currentDir->contains(*name, Directory::SearchType::DIRECTORY)) {
//            FETCH from HD the directory from block
                HW_HardDisk::blockNumber number = currentDir->getEnty(*name).getBlockIndex();
//            Carregar o diretorio na variavel currentDIr
//            Depois se for o ultimo da lista retorna
            } else {
                throw NO_DIR_PATH_ERROR;
            }
        }
    }

    return currentDir;
}
