#ifndef HTTPSERVER_H
#define HTTPSERVER_H

class HttpServer {
public:
    HttpServer();
    void work();

private:
    int socketFileDescriptor;
};

#endif // HTTPSERVER_H
