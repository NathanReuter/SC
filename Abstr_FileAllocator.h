/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileAllocator.h
 * Author: cancian
 *
 * Created on 9 de Setembro de 2016, 10:13
 */

#ifndef FILEALLOCATOR_H
#define FILEALLOCATOR_H

#include "Abstr_FileAllocationTable.h"


/**
 * Abstract class the represents an algorithm for file allocation. Possible implementations include contiguous, linked, indexed, ...
 * @param disk The disk that allocator allocates files in.
 * @param fat The file allocation table to register allocations
 */
class FileAllocator {
public:
    FileAllocator(HardDisk* disk, FileAllocationTable* fat);
    FileAllocator(const FileAllocator& orig);
public:
    HW_HardDisk::blockNumber createFile(const char *path);
    void removeFile(const unsigned char* path);
    
    FileAllocationEntry::fileIdentifier openFile(const char* path);
    void closeFile(const FileAllocationEntry::fileIdentifier file);
    
    unsigned int readFile(const FileAllocationEntry::fileIdentifier file, const unsigned int numBytes, char* bufferBytes);
    unsigned int writeFile(const FileAllocationEntry::fileIdentifier file, const unsigned int numBytes, char* bufferBytes);
    
    void seek(const unsigned long numByte);
    bool hasFreeBlocks();
    HW_HardDisk::blockNumber getNextFreeBlock();
private:
private:
    FileAllocationEntry::fileIdentifier getNewId();
    HardDisk* disk;
    FileAllocationTable* fat;
    FileAllocationEntry::fileIdentifier rootEntry;
    FileAllocationEntry::fileIdentifier fileCount = 0;
    std::vector<HW_HardDisk::blockNumber> freeBlocks;
};

#endif /* FILEALLOCATOR_H */

