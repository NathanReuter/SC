//
// Created by nathan on 21/10/16.
//

#include "Abstr_FileAllocationTable.h"

FileAllocationEntry::FileAllocationEntry(fileIdentifier inode, HW_HardDisk::blockNumber block,
                                         FileAttributes attributes) : inode(inode), block(block), attributes(attributes) {

}

HW_HardDisk::blockNumber FileAllocationEntry::getBlock() {
    return block;
}

FileAllocationEntry::fileIdentifier FileAllocationEntry::getNode() {
    return inode;
}

FileAttributes FileAllocationEntry::getAttributes() {
    return attributes;
}

void FileAllocationEntry::setAttributes(FileAttributes attributes) {
    this->attributes = attributes;
}

void FileAllocationEntry::setBlock(HW_HardDisk::blockNumber block) {
    this->block = block;
}

void FileAllocationEntry::setNode(fileIdentifier inode) {
    this->inode = inode;
}