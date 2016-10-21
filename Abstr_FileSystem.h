/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileSystem.h
 * Author: cancian
 *
 * Created on 29 de Agosto de 2016, 14:55
 */

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Abstr_FileAllocationTable.h"
#include "Abstr_FileAllocator.h"

/* Deve implementar o conceito de sistema de arquivos, como criar arquivo, procurar arquivo, deletar arquivo,
 * hierarquia de arquivos etc. Ainda não implementada.
 * Deve ser implementada para os temas 1.10, e possivelmente 1.11.*/

class FileSystem {
    friend class ProblemTester;
public:
    FileSystem();
    FileSystem(const FileSystem& orig);
    virtual ~FileSystem();
public:
    // INSERT YOUR CODE HERE
    int createFile();
//    FileAllocationEntry::fileIdentifier searchFile(const unsigned char* path);
//    int deleteFile();
    // ...
private:
    FileAllocator * fileAllocator;
};

#endif /* FILESYSTEM_H */

