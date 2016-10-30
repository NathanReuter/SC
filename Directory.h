//
// Created by nathan on 28/10/16.
//

#ifndef INC_20162_INE5412_SC_THEME1_STARTPOINT_MASTER_DIRECTORY_H
#define INC_20162_INE5412_SC_THEME1_STARTPOINT_MASTER_DIRECTORY_H

#include "HW_HardDisk.h"

/* Class that represents a directory*/

class DirectoryEntry {
    public:
        enum entryType {FILE, DIRECTORY};
    public:
        DirectoryEntry(const char* dirName, HW_HardDisk::blockNumber blockIndex, DirectoryEntry::entryType type);

    public:
        const char *getName() const;
        void setName(const char *name);
        HW_HardDisk::blockNumber getBlockIndex() const;
        void setBlockIndex(HW_HardDisk::blockNumber blockIndex);
        entryType getType() const;
        void setType(entryType type);

private:
        const char* name;
        HW_HardDisk::blockNumber blockIndex;
        entryType type;
};

class Directory {
    public:
        enum SearchType {FILE, DIRECTORY, BOTH};
    public:
        Directory(const char* name);

    public:
        void addDirEntry(DirectoryEntry entry);
        void removeDirEntry(const char* name);
        DirectoryEntry getEnty(const char * name);
        bool contains(const char * filename, SearchType type);
        std::list<const char*> listContent();
        const char* getDirectoryName();
        void renameDirectory(const char* newName);

    private:
        const char* name;
        std::list<DirectoryEntry> entries;
};


#endif //INC_20162_INE5412_SC_THEME1_STARTPOINT_MASTER_DIRECTORY_H
