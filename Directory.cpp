//
// Created by nathan on 28/10/16.
//

#include <iostream>
#include "Directory.h"

Directory::Directory(const char *name) : name(name){};

void Directory::addDirEntry(DirectoryEntry entry) {
//    TODO CHECK IF NEW ENTRY HAS SAME NAME IN DIRECTORY
    entries.push_back(entry);
}

std::list<const char*> Directory::listContent() {
    std::list<const char*> list;

    for (std::list<DirectoryEntry>::iterator entry = entries.begin(); entry != entries.end(); entry++) {
        list.push_back(entry->getName());
    }

    return list;
}

void Directory::removeDirEntry(const char *name) {
    for (std::list<DirectoryEntry>::iterator entry = entries.begin(); entry != entries.end(); entry++) {
        if (entry->getName() == name) {
            entries.erase(entry);
        }
    }
}

const char* Directory::getDirectoryName() {
    return name;
}

bool Directory::contains(const char *filename, SearchType type) {
    for (std::list<DirectoryEntry>::iterator entry = entries.begin(); entry != entries.end(); entry++) {
        if (filename == entry->getName()) {
            if (type != BOTH) {
                if (type == entry->getType()) {
                    return true;
                }
            } else {
                return true;
            }
        }
    }

    return false;
}

void Directory::renameDirectory(const char *newName) {
    name = newName;
}

DirectoryEntry Directory::getEnty(const char * name) {
    for (std::list<DirectoryEntry>::iterator entry = entries.begin(); entry != entries.end(); entry++) {
        if (entry->getName() == name) {
            return *entry;
        }
    }
}