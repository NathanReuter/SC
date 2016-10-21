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

FileSystem::FileSystem() {
    fileAllocator = new FileAllocator(OperatingSystem::HardDisk_Mediator(),
                                      new FileAllocationTable(OperatingSystem::HardDisk_Mediator()));
}

FileSystem::FileSystem(const FileSystem& orig) {
}

FileSystem::~FileSystem() {
}

int FileSystem::createFile() {
    fileAllocator->createFile();
    return 0;
}
