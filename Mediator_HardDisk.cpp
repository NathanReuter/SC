/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HD.cpp
 * Author: cancian
 * 
 * Created on 29 de Agosto de 2016, 14:46
 */

#include <cstring>
#include "Mediator_HardDisk.h"
#include "HW_Machine.h"

HardDisk::HardDisk(unsigned int instance) {
    _instance = instance;
    HW_HardDisk* hd = HW_Machine::HardDisk();
    hd->setCommandRegister(HW_HardDisk::GET_SECTORSIZE);
    _blocksize = hd->getDataRegister();
    hd->setCommandRegister(HW_HardDisk::GET_TOTALSECTORS);
    _maxBlocks = hd->getDataRegister();
    hd->setCommandRegister(HW_HardDisk::GET_SURFACES);
}

HardDisk::HardDisk(const HardDisk& orig) {
}

HardDisk::~HardDisk() {
}

void HardDisk::interrupt_handler() {     // Hard Disk Interrupt Handler
    // INSERT YOUR CODE HERE
    // ...
    
}

void HardDisk::flush() {
    
}

void HardDisk::writeBlock(DiskAccessRequest* request) {
    HW_HardDisk* hd = HW_Machine::HardDisk();
    hd->setDataRegister(request->GetBlockNumber());
    hd->setStreamRegister(request->GetDiskSector()->data);
    hd->setCommandRegister(HW_HardDisk::WRITE_LOGICALSECTOR);
}


void HardDisk::readBlock(DiskAccessRequest* request) {
    HW_HardDisk* hd = HW_Machine::HardDisk();
    hd->setDataRegister(request->GetBlockNumber());
    hd->setCommandRegister(HW_HardDisk::READ_LOGICALSECTOR);
    memcpy(request->GetDiskSector()->data, hd->getStreamRegister(), sizeof(request->GetDiskSector()->data));
}

void HardDisk::setBlockSize(const unsigned int blocksize) {
    
}

void HardDisk::accessBlock(DiskAccessRequest* request) {
    if (request->GetOperation() == DiskAccessRequest::READ) {
        readBlock(request);
    } else {
        writeBlock(request);
    }
        
}

unsigned int HardDisk::getBlockSize() {
    return _blocksize;
}

void HardDisk::setMaxBlocks(const HW_HardDisk::blockNumber maxBlocks) {
    
}

HW_HardDisk::blockNumber HardDisk::getMaxBlocks() {
    return _maxBlocks;
}
