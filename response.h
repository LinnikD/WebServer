#ifndef RESPONSE_H
#define RESPONSE_H


class Response {
public:
    Response();
    void setDate();
    void setStatusCode(int status);
    void setHttpVersion(std::string version);
    void setConnection(std::string connectionStatus);
    void setContentType(std::string type);
    void setContentLength(unsigned size);
    std::string getResponse();
    std::string getStatusCode();
private:
    std::string statusCode;
    std::string httpVersion;
    std::string connection;
    std::string date;
    std::string contentType;
    unsigned contentLength;
};

#endif // RESPONSE_H
