#ifndef HTTPSERVER_H
#define HTTPSERVER_H


#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <string.h>
#include <sys/stat.h>
#include <sstream>
#include <vector>
#include <mutex>

#include "worker.h"
#include "request.h"
#include "filesystem.h"
#include "response.h"
#include "decoder.h"


class HttpServer {
public:
    HttpServer(int work, int workersNum);
    void work();
private:
    int socketFileDescriptor;
    std::vector<Worker> workers;
    int workersNumber;
    std::mutex g_lockprint;

    void initWorkers();
    int getFreeWorker();
};

#endif // HTTPSERVER_H
