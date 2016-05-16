#ifndef SERIAL_XMEGA_H_
#define SERIAL_XMEGA_H_

#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>
#include <SerialStream.h>

#define RET_SUCCESS 0

int SerialInit(const char* Device, int iBaud, std::function<void (char*)> cbDataRcvd, std::string& sMsgErr);
int SerialCommunication(LibSerial::SerialStream& S, std::function<void (char*)> cbDataRcvd);

#endif
