/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileAllocator.cpp
 * Author: cancian
 * 
 * Created on 9 de Setembro de 2016, 10:13
 */

#include <iostream>
#include "Abstr_FileAllocator.h"

FileAllocator::FileAllocator(HardDisk* disk, FileAllocationTable* fat) {
    this->disk = disk;
    this->fat = fat;
    /* Creates a root entry directory*/
    FileAttributes rootAtt = FileAttributes();
    rootAtt.setFilename("/");
    rootAtt.setType(FileAttributes::fileType::dir);
    this->rootEntry = getNewId();
//    fat->addFileEntry(FileAllocationEntry(this->fileCount, this->getNextFreeBlock(), rootAtt));
//    std::cout << "dsaddsa" << std::endl;
//    disk->writeBlock()
//    Initializing freeblocks
    for (int i = 0; i < disk->getMaxBlocks(); ++i) {
        freeBlocks.push_back(i);
    }
}

FileAllocator::FileAllocator(const FileAllocator& orig) {
}

HW_HardDisk::blockNumber FileAllocator::getNextFreeBlock() {
    HW_HardDisk::blockNumber block = freeBlocks.front();
    freeBlocks.erase(freeBlocks.begin());

    return block;
}
/* Create an file*/
HW_HardDisk::blockNumber FileAllocator::createFile(const char *path) {
    FileAttributes newFileAtt = FileAttributes();
    FileAllocationEntry fileEntry = FileAllocationEntry(this->fileCount, this->getNextFreeBlock(), newFileAtt);

    if (fat->addFileEntry(fileEntry) == 0) {
        FileAllocationEntry::fileIdentifier identifier = fileCount;
        this->fileCount++;
        disk->writeBlock(new DiskAccessRequest(DiskAccessRequest::Operation::WRITE, fileCount, new HW_HardDisk::DiskSector()));

        return this->fileCount - 1;
    }

    return -1;
}

bool FileAllocator::hasFreeBlocks() {
    if (freeBlocks.size() == 0) {
        return false;
    }

    return true;
}

FileAllocationEntry::fileIdentifier FileAllocator::getNewId() {
    return fileCount++;
}