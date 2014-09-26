#include "httpserver.h"


HttpServer::HttpServer(int port, int workersNum): workers(workersNum) {
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
            }
        }

        int freeWorker = getFreeWorker();
        workers[freeWorker].pushClient(acceptedFileDescriptor);
    }
}

void HttpServer::initWorkers() {
    for (unsigned i = 0; i < workers.size(); i++) {
        std::thread thr(&Worker::run, &workers[i], i);
        thr.detach();
    }
}

int HttpServer::getFreeWorker() {
    int buffWorker = 0;
    for (unsigned i = 1; i < workers.size(); i++) {
        if (workers[buffWorker].getClientsNumber() > workers[i].getClientsNumber()) {
            buffWorker = i;
        }
    }
    return buffWorker;
}

