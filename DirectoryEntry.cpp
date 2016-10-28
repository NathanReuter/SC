//
// Created by nathan on 28/10/16.
//

#include "Directory.h"

DirectoryEntry::DirectoryEntry(const char *dirName, HW_HardDisk::blockNumber blockIndex, DirectoryEntry::entryType type) :
name(dirName), blockIndex(blockIndex), type(type) {}

const char *DirectoryEntry::getName() const {
    return name;
}

void DirectoryEntry::setName(const char *name) {
    DirectoryEntry::name = name;
}

HW_HardDisk::blockNumber DirectoryEntry::getBlockIndex() const {
    return blockIndex;
}

void DirectoryEntry::setBlockIndex(HW_HardDisk::blockNumber blockIndex) {
    DirectoryEntry::blockIndex = blockIndex;
}

DirectoryEntry::entryType DirectoryEntry::getType() const {
    return type;
}

void DirectoryEntry::setType(DirectoryEntry::entryType type) {
    DirectoryEntry::type = type;
}
