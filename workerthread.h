#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H


#include <thread>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <condition_variable>

#include "connectionpull.h"
#include "request.h"
#include "response.h"
#include "filesystem.h"
#include "decoder.h"


class WorkerThread {
public:
    int testNumber;
    bool notified;
    std::condition_variable g_queuecheck;    
    WorkerThread() {
        clientsNumber = 0;
        notified = false;
    }
    void start();
    void wakeUp();
    unsigned long getClientsNumber();
    void setClient(int acceptedFileDescriptor);
private:
    std::mutex  _lock;
    ConnectionPull clients;
    unsigned long clientsNumber;
    void work(int acceptedFileDescriptor);
    int getClient();
};

#endif // WORKERTHREAD_H
