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