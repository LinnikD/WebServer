#ifndef FILESYSTEM_H
#define FILESYSTEM_H


#include <fstream>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <string>
#include <cstring>
#include <iostream>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


class FileSystem {
public:
    FileSystem();
    FileSystem(const std::string & path);

    bool fileExist(const std::string & path);
    bool isDirectory(const std::string & path);
    bool isFile(const std::string & path);
    unsigned getLength(const std::string & path);
    std::string getContentType(const std::string & path);
    char * getFile(const std::string & path);
    int openFileDescriptor(const std::string & path);
    void colseFileDescriptor(int fd);
private:
    char DIRECTORY_ROOT[512];
    struct stat st;

    int initSt(const char *path);
};

#endif // FILESYSTEM_H
