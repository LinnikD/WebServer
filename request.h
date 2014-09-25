#ifndef REQUEST_H
#define REQUEST_H

class Request
{
public:
    Request(char* requestBuffer);
    std::string getRequestMethod();
    std::string getRequestUrl();
    std::string getHttpVersion();
    void print();
private:
    std::string requestMethod;
    std::string requestUrl;
    std::string httpVersion;
};

#endif // REQUEST_H
