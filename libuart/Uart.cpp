#include "Uart.h"

// class with device and baud rate info 
// and func for callback


int SerialCommunication(LibSerial::SerialStream& S, std::function<void (char*)> cbDataRcvd)
{
	try
	{
		std::cout << "WE GET HERE" << std::endl;
		char cRxData[128], *pch = cRxData;
		while(S.good())
		{
			pch = cRxData; // Reset the data 
			std::memset(pch, '\0', sizeof(cRxData)); 

			while (S.rdbuf()->in_avail()) 
			{
				S.get(*pch);		
				pch++;
			}

			if (*cRxData != '\0')
				cbDataRcvd(cRxData);
			// S.write("8", sizeof("8"));
			usleep(80000); // 100ms 
		}
		std::cerr << "SerialStream broke, bye bye\n";
		return 8;
	}
	catch(std::exception e)
	{
		std::cout << "Exception@ SerialCommunication(): " << e.what() << '\n';
		return -100;
	}
	catch(...)
	{
		std::cout << "Exception@ SerialCommunication()"<< '\n';
		return -101;
	}
}

int SerialInit(char* pDevice, int iBaud, std::function<void (char*)> cbDataRcvd, std::string& sMsgErr)
{
	try
	{
		if (!pDevice)
		{
			sMsgErr = "Device is empty";
			return -1; 
		}

		LibSerial::SerialStreamBuf::BaudRateEnum eBaud;

		switch (iBaud) 
		{
			case 9600:
				eBaud = LibSerial::SerialStreamBuf::BAUD_9600;
				break;
			case 38400:
				eBaud = LibSerial::SerialStreamBuf::BAUD_38400;
				break;
			case 57600:
				eBaud = LibSerial::SerialStreamBuf::BAUD_57600;
				break;
			case 115200:
				eBaud = LibSerial::SerialStreamBuf::BAUD_115200;
				break;
			default:
				sMsgErr = "Wrong BaudRate selected";
				return -2;
		}

		LibSerial::SerialStream S(pDevice, eBaud);

		if (!S.IsOpen())
		{
			sMsgErr.append("Couldn't Open Device ").append(pDevice).append(" with Baudrate ");
			sMsgErr += iBaud;
			std::cout << sMsgErr << '\n';
			return -3;
		}

		return RET_SUCCESS;
	}
	catch(std::exception e)
	{
		std::cout << "Exception@ SerialInit(): " << e.what() << '\n';
		return -100;
	}
	catch(...)
	{
		std::cout << "Exception@ SerialInit()"<< '\n';
		return -101;
	}
}

class CustSerial {
	
	public:
		char* pDevice;
		int iBaudRate;
		CustSerial();
};
CustSerial::CustSerial() {
	
}
