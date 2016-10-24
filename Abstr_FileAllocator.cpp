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
}

FileAllocator::FileAllocator(const FileAllocator& orig) {
}

/* Create an file*/
FileAllocationEntry::fileIdentifier FileAllocator::createFile() {
    FileAttributes newFileAtt = FileAttributes();
    FileAllocationEntry fileEntry = FileAllocationEntry(this->fileCount, this->disk->getBlockSize(), newFileAtt);
    if (fat->addFileEntry(fileEntry) == 0) {
        FileAllocationEntry::fileIdentifier identifier = fileCount;
        this->fileCount++;

        return this->fileCount - 1;
    }
}