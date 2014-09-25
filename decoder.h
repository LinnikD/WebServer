#ifndef DECODER_H
#define DECODER_H

#include <iostream>
#include <string>
#include <cmath>
#include <cstring>

bool checkEntry(int num, int left, int right) ;

int hexToDec(const std::string & code) ;

std::string urlDecoder(const std::string & url);

std::string urlDeleteParams(const std::string & url);

#endif // DECODER_H
