#ifndef ODROID_H_
#define ODROID_H_

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include "SerialXmega.h"

int PrintMsg(const char *pMsg, const char *pThreadName);

#endif
