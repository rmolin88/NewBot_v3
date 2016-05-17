#include "Uart.h"

// class with device and baud rate info 
// and func for callback


int SerialCommunication(LibSerial::SerialStream& S, std::atomic_bool& atomicDataRdy, char* pData)
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
			{
				std::strcpy(pData,cRxData);
				while (!atomicDataRdy.is_lock_free()); // wait for the atomic to be lock free
				atomicDataRdy.store(true, std::memory_order_release); // set the data rdy flag 
			}
			S.write("Hello World", sizeof("Hello World"));
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

// TODO: make send function
