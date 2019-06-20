#ifndef GETURL
#define GETURL

#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>

int getVideoAddress(std::string *videoAddress);

#endif 
