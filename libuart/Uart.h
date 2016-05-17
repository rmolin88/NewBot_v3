#ifndef SERIAL_XMEGA_H_
#define SERIAL_XMEGA_H_

#include <iostream>
#include <cstring>
#include <atomic>
#include <SerialStream.h>

#define RET_SUCCESS 0

int SerialCommunication(LibSerial::SerialStream& S, std::atomic_bool& atomicDataRdy, char* pData);

#endif
