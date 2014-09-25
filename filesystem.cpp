#include <fstream>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <string>
#include <cstring>
#include <iostream>

#include "filesystem.h"


FileSystem::FileSystem() {
    strcpy(DIRECTORY_ROOT, "/home/uzzz/");
}

FileSystem::FileSystem(const std::string & path) {
    const char* c_path = path.c_str();
    strcpy(DIRECTORY_ROOT, c_path);

}

bool FileSystem::fileExist(const std::string & path) {
    const char* c_path = path.c_str();
    int status = initSt(c_path);
    if( status != 0 )
        return false;
    else
        return true;
}

bool FileSystem::isDirectory(const std::string & path) {
    const char* c_path = path.c_str();
    initSt(c_path);
    if (S_ISDIR (st.st_mode))
        return true;
    else
        return false;
}

bool FileSystem::isFile(const std::string & path) {
    const char* c_path = path.c_str();
    initSt(c_path);
    if (S_ISREG (st.st_mode))
        return true;
    else
        return false;
}

unsigned FileSystem::getLength(const std::string & path) {
    const char* c_path = path.c_str();
    initSt(c_path);
    return st.st_size;  // Do i need -1 ?
}

std::string FileSystem::getContentType(const std::string & path) {
    size_t pos = path.find_last_of(".");
    std::string type = "";
    if(pos == std::string::npos)
        return type;
    for(unsigned i = pos; i < path.length(); i++)
        type += path[i];
    return type;
}

char * FileSystem::getFile(const std::string & path) {
    char *absPath = new char[512];
    strcpy(absPath, DIRECTORY_ROOT);
    strcat(absPath, path.c_str() );
    std::ifstream stream(absPath, std::ios::in | std::ios::binary);
    size_t fileSize = this->getLength(path);
    char *buf = new char[fileSize];
    stream.read(buf, fileSize);
    stream.close();
    delete[] absPath;
    return buf;
}

int FileSystem::initSt(const char *path) {
    char *absPath = new char[512];
    strcpy(absPath, DIRECTORY_ROOT);
    strcat(absPath, path);
    int status = stat(absPath, &st);
    delete[] absPath;
    return status;
}

