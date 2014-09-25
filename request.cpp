#include <iostream>
#include <string>

#include "request.h"


Request::Request(char* requestBuffer) {
    requestMethod = "";
    requestUrl = "";
    httpVersion = "";

    while(*requestBuffer != ' ')
        requestMethod += *requestBuffer++;

    requestBuffer++;
    while(*requestBuffer != ' ')
        requestUrl += *requestBuffer++;

    requestBuffer++;
    while(*requestBuffer != '\n')
        httpVersion += *requestBuffer++;
}

std::string Request::getRequestMethod() {
    return requestMethod;
}
std::string Request::getRequestUrl() {
    return requestUrl;
}
std::string Request::getHttpVersion() {
    return httpVersion;
}

void Request::print() {
    std::cout << std::endl << "requestMethod: "<< requestMethod
              << std::endl << "requestUrl: "<< requestUrl
              << std::endl << "httpVersion: " << httpVersion
              << std::endl;
}
