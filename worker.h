#ifndef WORKER_H
#define WORKER_H


#include <thread>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <condition_variable>

#include "clientsqueue.h"
#include "request.h"
#include "response.h"
#include "filesystem.h"
#include "decoder.h"


static std::recursive_mutex g_lockprint;

class Worker { 
public:
    int testNumber;
    bool notified;
    std::condition_variable g_queuecheck;    
    Worker();
    void run(int t);
    void wakeUp();
    unsigned long getClientsNumber();
    void pushClient(int acceptedFileDescriptor);
private:
    std::mutex  _lock;
    ClientsQueue clients;
    unsigned long clientsNumber;
    int workerIndex;
    void execute(int acceptedFileDescriptor);
    int popClient();
};

#endif // WORKER_H
