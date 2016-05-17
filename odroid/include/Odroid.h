#ifndef ODROID_H_
#define ODROID_H_

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <string>
#include <cstring>
#include <SerialStream.h>

#define CHAR_SIZE 32
#define RET_SUCCESS 0
#define BAUD 115200

int PrintMsg(const std::string& sMsg, const std::string& sThreadName);
int SerialCommunication(LibSerial::SerialStream& S, std::atomic_bool& atomicDataRdy, char* pData);

#endif
