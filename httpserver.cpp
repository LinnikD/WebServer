#include "httpserver.h"


HttpServer::HttpServer(int port, int workersNum): workerThreadPull(workersNum) {
    workersNumber = workersNum;

    std::cout << "Init web server: ";
    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFileDescriptor < 0) {
        std::cout << "Socket Initialization Failed" << std::endl;
        return;
    }

    sockaddr_in socketAddres;
    socketAddres.sin_family = AF_INET;
    socketAddres.sin_port = htons(port);
    socketAddres.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int bindStatus = bind(socketFileDescriptor, (sockaddr *) &socketAddres, sizeof(sockaddr));
    if(bindStatus == -1) {
        std::cout << "Bind Error" << std::endl;
        return;
    }

    int listenStatus = listen(socketFileDescriptor, 1000);
    if(listenStatus == -1) {
        std::cout << "Listen Error" << std::endl;
        return;
    }

    std::cout << "OK" << std::endl << "Listening ... " << std::endl << std::endl;
}

void HttpServer::work() {

    initWorkers();

    while(1) {
        int acceptedFileDescriptor = accept(socketFileDescriptor, NULL, NULL);
        {
            if(acceptedFileDescriptor == -1) {
                std::cout << "Accept connected client error" << std::endl;
                return;
            }
        }

        int wt = chooseWorkerThread();
            workerThreadPull[wt].setClient(acceptedFileDescriptor);
    }
}

void HttpServer::initWorkers() {
    for (unsigned i = 0; i < workerThreadPull.size(); i++) {
        std::thread thr(&WorkerThread::start, &workerThreadPull[i]);
        thr.detach();
    }
}

int HttpServer::chooseWorkerThread() {
    int worker = 0;
    for (unsigned i = 1; i < workerThreadPull.size(); i++) {
        if (workerThreadPull[worker].getClientsNumber() > workerThreadPull[i].getClientsNumber()) {
            worker = i;
        }
    }
    return worker;
}

