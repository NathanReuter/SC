/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileAllocationTable.cpp
 * Author: cancian
 * 
 * Created on 9 de Setembro de 2016, 10:14
 */

#include <iostream>
#include "Abstr_FileAllocationTable.h"
#define FULL_TABLE_ERROR -1

FileAllocationTable::FileAllocationTable(HardDisk* disk) : disk(disk){
}

FileAllocationTable::FileAllocationTable(const FileAllocationTable& orig) {
}

int FileAllocationTable::addFileEntry(FileAllocationEntry fatEntry) {
    if (table.size() < disk->getMaxBlocks()) {
        table.push_back(fatEntry);

        return 0;
    }

    return FULL_TABLE_ERROR;
}

FileAllocationEntry FileAllocationTable::getFileEntryByRank(unsigned int rank) {
    return table[rank];
}

FileAllocationEntry FileAllocationTable::getFileEntryByNode(FileAllocationEntry::fileIdentifier inode) {
    for (std::vector<FileAllocationEntry>::iterator entry = table.begin(); entry != table.end(); ++entry) {
        if (inode == entry->getNode()) {
            return *entry;
        }
    }
}

void FileAllocationTable::removeFileEntryByNode(FileAllocationEntry::fileIdentifier inode) {
    for (std::vector<FileAllocationEntry>::iterator entry = table.begin(); entry != table.end(); ++entry) {
        if (inode == entry->getNode()) {
            table.erase(entry);
        }
    }
}

void FileAllocationTable::removeFileEntryByRank(unsigned int rank) {
    table.erase(table.begin() + rank);
}

void FileAllocationTable::setFileEntry(unsigned int rank, FileAllocationEntry fatEntry) {
    removeFileEntryByNode(fatEntry.getNode());
    table.insert(table.begin() + rank, fatEntry);
}