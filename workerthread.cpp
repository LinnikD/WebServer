#include "workerthread.h"




unsigned long WorkerThread::getClientsNumber() {
    return clientsNumber;
}

void WorkerThread::setClient(int acceptedFileDescriptor) {
    clients.setClient(acceptedFileDescriptor);
    clientsNumber = clients.getClientsNumber();
    wakeUp();
}

int WorkerThread::getClient() {
    int buff = clients.getClient();
    clientsNumber = clients.getClientsNumber();
    return buff;
}

void WorkerThread::work(int acceptedFileDescriptor) {
    
    char buffer[1024];
    
    bool readingData = true;
    while( readingData ) {
        int bytesReaded = (int)recv(acceptedFileDescriptor, &buffer, 1024, 0);
        if(bytesReaded == 0) {
            break;
        }
        int a = memcmp(buffer + bytesReaded - 4, "\r\n\r\n", 4);
        if( a == 0 )
            readingData = false;
    }
    
    Request r(buffer);
    
    Response resp;
    char* buf = NULL;
    FileSystem *fs = new FileSystem();
    
    std::string url =  urlDeleteParams( urlDecoder(r.getRequestUrl()) );
    std::string method = r.getRequestMethod();
    
    if( !(method == "GET" || method == "HEAD") ) {
        resp.setStatusCode(405);
        resp.setContentLength(0);
        resp.setConnection("close");
        resp.setDate();
    }
    else {
        if( !fs->fileExist(url)) {
            resp.setStatusCode(404);
            resp.setContentLength(0);
            resp.setConnection("close");
            resp.setDate();
        }
        if(fs->isDirectory(url)) {
            url += "/index.html";
            if(!fs->fileExist(url)) {
                resp.setStatusCode(403);
                resp.setContentLength(0);
                resp.setConnection("close");
                resp.setDate();
            }
        }
        
        if(fs->isFile( url )) {
            size_t fileSize = fs->getLength( url ) ;
            resp.setDate();
            resp.setStatusCode(200);
            resp.setContentLength((int)fileSize);
            resp.setContentType( fs->getContentType( url ) );
            resp.setConnection("close");
            
        }
        
    }
    std::string respStr = resp.getResponse();

    ssize_t s = send(acceptedFileDescriptor, respStr.c_str(), respStr.length(), MSG_NOSIGNAL);
    if (s == -1 && errno == EPIPE) {

    }



    if(method == "GET" && resp.getStatusCode() == "200 OK" ) {
        size_t fileSize = fs->getLength( url ) ;



        // Замена send() на sendfile()
        /*
        char *buf = fs->getFile( url );
        if(buf != NULL) {
            s = send(acceptedFileDescriptor, buf, fileSize, MSG_NOSIGNAL);
            if (s == -1 && errno == EPIPE) {
            }
        }
        */


        int fd = fs->openFileDescriptor( url );
        ssize_t status = sendfile (acceptedFileDescriptor, fd, NULL, fileSize);
        if(status == -1 && errno == EINVAL) {
            std::cout << "/n Error in sendfile, sorry /n";
        }
        fs->colseFileDescriptor( fd );

        delete[] buf;
        buf = NULL;
    }



    
    delete[] buf;
    delete fs;
    buf = NULL;
    
    close(acceptedFileDescriptor);
}

void WorkerThread::start() {
    while (1) {
        std::unique_lock<std::mutex> locker(_lock);
        while(!notified) {
            g_queuecheck.wait(locker);
        }
        while (getClientsNumber()) {
            work(getClient());
        }
        notified = false;
    }
}

void WorkerThread::wakeUp() {
    notified = true;
    g_queuecheck.notify_all();
}
