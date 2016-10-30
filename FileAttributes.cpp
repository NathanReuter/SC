//
// Created by nathan on 21/10/16.
//

#include <iostream>
#include "Abstr_FileAllocationTable.h"
using namespace std;

FileAttributes::FileAttributes() {
}

void FileAttributes::setFilename(const char *filename) {
    this->filename = filename;
}

void FileAttributes::setSize(unsigned long size) {
    this->size = size;
}

void FileAttributes::setType(fileType type) {
    this->type = type;
}

const char* FileAttributes::getFilename() {
    return filename;
}

unsigned long FileAttributes::getSize() {
    return size;
}

FileAttributes::fileType FileAttributes::getType() {
    return type;
}

void FileAttributes::showAttributes() {
    cout << "File Name: " << filename << endl
         << "File Size: " << size << endl
         << "File Type: " << type << endl;
}