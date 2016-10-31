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
    void createFile(const char *path, FileAttributes newFileAtt);
    void removeFile(const unsigned char* path);
    
    FileAllocationEntry::fileIdentifier openFile(const char* path);
    void closeFile(const FileAllocationEntry::fileIdentifier file);
    
    unsigned int readFile(const FileAllocationEntry::fileIdentifier file, const unsigned int numBytes, char* bufferBytes);
    unsigned int writeFile(const FileAllocationEntry::fileIdentifier file, const unsigned int numBytes, char* bufferBytes);

    bool hasFreeBlocks();
    HW_HardDisk::blockNumber getNextFreeBlock();
private:
    void initRootDirectory();
    std::string newFileDiskData(FileAttributes att, std::list<int> nodes);
    std::string createAttributesDiskData(FileAttributes att);
    std::string createFileDiskInodes(std::list<int> nodes);
    std::string createDirEntry(int block, FileAttributes att);
    std::list<int> getFileDisksInodes(const char *fileData);
    void writeToDisk(HW_HardDisk::blockNumber block, std::string data);
    std::string readFromDisk(HW_HardDisk::blockNumber block);
    const char * readFileInode();
private:
    FileAllocationEntry::fileIdentifier getNewId();
    HardDisk* disk;
    FileAllocationTable* fat;
    FileAllocationEntry::fileIdentifier rootEntry;
    FileAllocationEntry::fileIdentifier fileCount = 0;
    std::vector<HW_HardDisk::blockNumber> freeBlocks;
};

#endif /* FILEALLOCATOR_H */

