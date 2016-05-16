#ifndef ODROID_H_
#define ODROID_H_

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <string>
#include <cstring>
#include <functional>

#define CHAR_SIZE 32
#define RET_SUCCESS 0
#define BAUD 115200

int PrintMsg(const std::string& sMsg, const std::string& sThreadName);
int SerialInit(const std::string& sDevice, int iBaud, std::function<void (char*)> cbDataRcvd, std::string& sMsgErr);

#endif
