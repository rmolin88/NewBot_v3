#ifndef SERIAL_XMEGA_H_
#define SERIAL_XMEGA_H_

#include <iomanip>
#include <SerialStream.h>

#define RET_SUCCESS 0

int SerialCommunication(LibSerial::SerialStream& S);
int SerialInit(LibSerial::SerialStream& S, const char *pDevice);

#endif
