#include "Uart.h"

// class with device and baud rate info 
// and func for callback

static int SerialCommunication(LibSerial::SerialStream& S, std::function<int (char*)>& cbDataRcvd);

static int SerialCommunication(LibSerial::SerialStream& S, std::function<int (char*)>& cbDataRcvd)
{
	try
	{
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
			S.write("8", sizeof("8"));
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
}

int SerialInit(char* pDevice, int iBaud, std::function<int (char*)>& cbDataRcvd, char *pMsgErr)
{
	try
	{
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
				std::sprintf(pMsgErr, "Wrong BaudRate selected");
				return -2;
		}

		LibSerial::SerialStream S(pDevice, eBaud);

		// TODO: move this line to odroid.main()
		// std::future<char*> futureRxData = promiseRxData.get_future();
		if (S.IsOpen())
			std::thread tSerial(SerialCommunication, std::ref(S), std::ref(cbDataRcvd));	
		else
		{
			std::sprintf(pMsgErr, "Couldn't Open Device %s", pDevice);
			return -3;
		}

		return RET_SUCCESS;
	}
	catch(std::exception e)
	{
		std::cout << "Exception@ SerialInit(): " << e.what() << '\n';
		return -100;
	}
}

