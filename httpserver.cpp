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

#include "httpserver.h"
#include "request.h"
#include "filesystem.h"
#include "response.h"
#include "decoder.h"

HttpServer::HttpServer() {
    std::cout << "Init web server: ";
    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFileDescriptor < 0) {
        std::cout << "Socket Initialization Failed" << std::endl;
    }

    sockaddr_in socketAddres;
    socketAddres.sin_family = AF_INET;
    socketAddres.sin_port = htons(8080);
    socketAddres.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int bindStatus = bind(socketFileDescriptor, (sockaddr *) &socketAddres, sizeof(sockaddr));
    if(bindStatus == -1) {
        std::cout << "Bind Error" << std::endl;
    }

    int listenStatus = listen(socketFileDescriptor, 5);
    if(listenStatus == -1) {
        std::cout << "Listen Error" << std::endl;
    }

    std::cout << "OK" << std::endl << "Listening ... " << std::endl << std::endl;
}

void HttpServer::work() {
    while(1) {
        int acceptedFileDescriptor = accept(socketFileDescriptor, NULL, NULL);
        if(acceptedFileDescriptor == -1) {
            std::cout << "Accept connected client error" << std::endl;
            break;
        }
        char buffer[1024];

        bool readingData = true;
        while( readingData ) {
            int bytesReaded = recv(acceptedFileDescriptor, &buffer, 1024, 0);
            if(bytesReaded == 0) {
                std::cout << "Reading data error" << std::endl;
                break;
            }
            readingData = memcmp(buffer + bytesReaded - 4, "\r\n\r\n", 4);
        }




        Request r(buffer);
        r.print();
        std::cout << "\n\n";

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
                std::cout << "HEREEE";
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
                resp.setContentLength(fileSize);
                resp.setContentType( fs->getContentType( url ) );
                resp.setConnection("close");

            }

        }
        std::string respStr = resp.getResponse();
        std::cout << respStr;
        send(acceptedFileDescriptor, respStr.c_str(), respStr.length(), 0);
        if(method == "GET" && resp.getStatusCode() == "200 OK" ) {
            size_t fileSize = fs->getLength( url ) ;
            char *buf = fs->getFile( url );
            if(buf != NULL)
                send(acceptedFileDescriptor, buf, fileSize, 0);
        }
        std::cout << "\n\n";

        delete[] buf;
        delete fs;
        buf = NULL;
    }
}
