#ifndef ODROID_H_
#define ODROID_H_

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include "SerialXmega.h"

#define CHAR_SIZE 32

int PrintMsg(const char *pMsg, const char *pThreadName);

#endif
