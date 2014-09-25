#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <string.h>
#include <fstream>
#include <sstream>


#include <sys/stat.h>


#include "request.h"
#include "filesystem.h"
#include "httpserver.h"


class Response {
public:
    Response() {

    }
private:
    std::string statusCode;
    std::string httpVersion;
    std::string connection;
    std::string date;
    std::string contentType;
    std::string contentLength;
};

class WorkerThread {

};
/*
class HttpServer {
public:
    HttpServer() {
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

    void work() {
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

            std::string url("/home/uzzz/Firefox_wallpaper.png");

            FileSystem fs;
            size_t fileSize = fs.getLength( url ) ;
            char *buf = fs.getFile( url );

            std::stringstream ss;
            ss << "HTTP/1.1 200 OK\r\nContent-Length: "
               << fileSize << "\r\nContent_type: image/jpg\r\nConnection: close\r\n\r\n";

            std::string msg_str = ss.str();
            const char* msg = msg_str.c_str();
            size_t msg_size = msg_str.length();


            send(acceptedFileDescriptor, msg, msg_size, 0);
            send(acceptedFileDescriptor, buf, fileSize, 0);

            delete[] buf;
        }
    }

private:
    int socketFileDescriptor;
};
*/

int main() {

    HttpServer server;
    server.work();

    /*
    std::cout << "Init socket : ";
    int socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFileDescriptor < 0) {
        std::cout << "Socket Initialization Failed" << std::endl;
        return -1;
    }
    std::cout << "Done" << std::endl;

    sockaddr_in socketAddres;
    socketAddres.sin_family = AF_INET;
    socketAddres.sin_port = htons(8080);
    socketAddres.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    std::cout << "Bind socket : ";
    int bindStatus = bind(socketFileDescriptor, (sockaddr *) &socketAddres, sizeof(sockaddr));
    if(bindStatus == -1) {
        std::cout << "Bind Error" << std::endl;
    }
    std::cout << "Done" << std::endl;

    std::cout << "Listen socket: ";
    int listenStatus = listen(socketFileDescriptor, 5);
    if(listenStatus == -1) {
        std::cout << "Listen Error" << std::endl;
    }
    std::cout << "Done" << std::endl<<std::endl;

    while(1) {
        int acceptedFileDescriptor = accept(socketFileDescriptor, NULL, NULL);
        if(acceptedFileDescriptor == -1) {
            std::cout << "Accept connected client error" << std::endl;
            break;
        }
        std::cout << "Client connected : " << std::endl << std::endl;

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
        //for(int i = 0; buffer[i] != '\0'; i++) {
        //    std::cout << buffer[i];
        //}
        //std::cout << std::endl << std::endl;


        std::string url("/home/uzzz/Firefox_wallpaper.png");
        //std::ifstream stream (url.c_str(), std::ios::in | std::ios::binary);

        FileSystem fs;
        size_t fileSize = fs.getLength( url ) ;
        char *buf = fs.getFile( url );

      //  std::cout << fileSize << std::endl;

     //   stream.read(buf, fileSize);
       // stream.close();


        std::stringstream ss;
        ss << "HTTP/1.1 200 OK\r\nContent-Length: "
           << fileSize << "\r\nContent_type: image/jpg\r\nConnection: close\r\n\r\n";

        std::string msg_str = ss.str();
        const char* msg = msg_str.c_str();
        size_t msg_size = msg_str.length();


//        char *msg = new char[10000];
//        char first[] = ;
//        strcpy(msg, first);
//        std::string sizeStr = std::to_string(fileSize);
//        strcat(msg, sizeStr.c_str() );

//        strcat(msg, "\r\nContent_type: image/jpg\r\nConnection: close\r\n\r\n");

        send(acceptedFileDescriptor, msg, msg_size, 0);
        send(acceptedFileDescriptor, buf, fileSize, 0);
//        delete [] msg;
        delete[] buf;

    }

    */

    return 0;
}
