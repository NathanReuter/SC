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
#include <cstring>
#include "Abstr_FileAllocator.h"
#include <string>

FileAllocator::FileAllocator(HardDisk* disk, FileAllocationTable* fat) {
    this->disk = disk;
    this->fat = fat;
    /* Initializing freeblocks */
    for (int i = 0; i < disk->getMaxBlocks(); ++i) {
        freeBlocks.push_back(i);
    }

    initRootDirectory();
}
void FileAllocator::initRootDirectory() {
    /*Init root Atributes */
    FileAttributes rootAtt = FileAttributes();
    rootAtt.setFilename("/");
    rootAtt.setType(FileAttributes::fileType::dir);
    rootAtt.setSize(0);
    this->rootEntry = getNewId();
    HW_HardDisk::blockNumber block = getNextFreeBlock();
    /* Adding to the Fat table */
    fat->addFileEntry(FileAllocationEntry(this->rootEntry, block, rootAtt));
    std::list<int> rootNodesList;
    rootNodesList.push_back(getNextFreeBlock());
    /* Writting atributes do the disk */
    HW_HardDisk::DiskSector * ds2 = new HW_HardDisk::DiskSector();
    writeToDisk(block, newFileDiskData(rootAtt, rootNodesList));
    std::cout << "##reading data: " << readFromDisk(block) << std::endl;
}

FileAllocator::FileAllocator(const FileAllocator& orig) {
}

std::list<int> FileAllocator::getFileDisksInodes(const char *fileData) {
    std::list<int> nodeslist;
    std::string inodesSection = std::string(fileData), finalString;
    finalString = inodesSection.substr(inodesSection.find("#idnodes#") + std::string("#idnodes#").size());
    std::string delimiter = ";";
    size_t pos = 0;
    std::string token;

    while ((pos = finalString.find(delimiter)) != std::string::npos) {
        token = finalString.substr(0, pos);
        nodeslist.push_back(std::stoi(token));
        finalString.erase(0, pos + delimiter.length());
    }
    std::cout << finalString << std::endl;

    return nodeslist;
}

HW_HardDisk::blockNumber FileAllocator::getNextFreeBlock() {
    HW_HardDisk::blockNumber block = freeBlocks.front();
    freeBlocks.erase(freeBlocks.begin());

    return block;
}
/* Create an file*/
void FileAllocator::createFile(const char *path, FileAttributes newFileAtt) {
//    Search path
    if (hasFreeBlocks()) {
        FileAllocationEntry currentDir = fat->getFileEntryByNode(rootEntry);
        std::cout <<  " asdsadasdsad"<< currentDir.getAttributes().getFilename() << std::endl;
        /* Pegar os inodes do diretorio e escrever a entrada no arquivo no bloco livre*/
        /*Pega o ultimo nodo (pois os outros devem estar cheios)*/
        int lastDataBlock = getFileDisksInodes(readFromDisk(currentDir.getBlock()).c_str()).back();
        /*Faz um novo acesso a esse bloco */
        HW_HardDisk::blockNumber newFileBlock = getNextFreeBlock();
//      Adding a new file entry into current directory
        std::string dirData = readFromDisk(lastDataBlock);
        std::string newDirEntry = createDirEntry(newFileBlock, newFileAtt);

        /*  Verifica se ele está cheio ou não. Se nao o dado é gravado em outro bloco*/

        std::cout<< "SIZE SIZE: " << dirData.size() + newDirEntry.size() << std::endl;
        if (dirData.size() + newDirEntry.size() < disk->getBlockSize()) {
            /*File added to the fat table*/
            fat->addFileEntry(FileAllocationEntry(getNewId(), newFileBlock,  newFileAtt));

            /* File entry recorded in the directory */
            dirData += newDirEntry;
            writeToDisk(lastDataBlock, dirData);

            /* File data is recorded in new block*/
            std::list<int> rootNodesList;
            rootNodesList.push_back(getNextFreeBlock());
            writeToDisk(newFileBlock, newFileDiskData(newFileAtt, rootNodesList));
        } else {
////            write content in another block and store it
//            HW_HardDisk::blockNumber newDirBlock = getNextFreeBlock();
        }

        std::cout<< "DISK BLOK NOW: " << freeBlocks.front() << std::endl;
    }
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

std::string FileAllocator::newFileDiskData(FileAttributes att, std::list<int> nodes) {
    return createAttributesDiskData(att) + createFileDiskInodes(nodes);
}

std::string FileAllocator::readFromDisk(HW_HardDisk::blockNumber block) {
    HW_HardDisk::DiskSector * ds = new HW_HardDisk::DiskSector();
    disk->readBlock(new DiskAccessRequest(DiskAccessRequest::READ, block, ds));

    return std::string((char *) ds->data);
}

void FileAllocator::writeToDisk(HW_HardDisk::blockNumber block, std::string data) {
    HW_HardDisk::DiskSector * ds = new HW_HardDisk::DiskSector();
    memcpy(ds->data, data.c_str(), data.size());
    disk->writeBlock(new DiskAccessRequest(DiskAccessRequest::WRITE, block, ds));
}
std::string FileAllocator::createDirEntry(int block, FileAttributes att) {
    return  "#entry:"
            + std::string("filename") + att.getFilename()
            + std::string("block") + std::to_string(block)
            + std::string("type") +  std::to_string(att.getType());
}

std::string FileAllocator::createAttributesDiskData(FileAttributes att) {
    return  "#attr#"
            + std::string("name:") + att.getFilename()
            + std::string("size:") +  std::to_string(att.getSize())
            + std::string("type:") +  std::to_string(att.getType());
}

std::string FileAllocator::createFileDiskInodes(std::list<int> nodes) {
    std::string idnodesStr = "#idnodes#";

    for (std::list<int>::iterator node = nodes.begin(); node != nodes.end(); node++) {

        idnodesStr += std::to_string(*node) + std::string(";");
    }

    return idnodesStr;
}
