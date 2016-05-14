#ifndef ODROID_H_
#define ODROID_H_

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <cstring>
#include <functional>

#define CHAR_SIZE 32
#define RET_SUCCESS 0
#define BAUD 115200

int PrintMsg(const char *pMsg, const char *pThreadName);
int SerialInit(char* pDevice, int iBaud, std::function<void (char*)> cbDataRcvd, char *pMsgErr);

#endif
