#ifndef ODROID_H_
#define ODROID_H_

#include <iostream>
// #include <atomic>
// #include <chrono>
#include <future>

#define CHAR_SIZE 32
#define RET_SUCCESS 0
#define BAUD 115200

int PrintMsg(const char *pMsg, const char *pThreadName);
int SerialInit(char* pDevice, int iBaud, std::function<int (char*)>& cbDataRcvd);

#endif
