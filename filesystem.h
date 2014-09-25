#ifndef FILESYSTEM_H
#define FILESYSTEM_H

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

private:
    char DIRECTORY_ROOT[512];
    struct stat st;
    int initSt(const char *path);
};

#endif // FILESYSTEM_H
