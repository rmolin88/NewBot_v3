#include "Uart.h"

// class with device and baud rate info 
// and func for callback


void CustSerial::SerialCommunication()
{
	try
	{
		int k=0, k1=0;
		char cRxData[32] = {0}; // undefined behavior if you ever receive data larger than 32 
		char cTxData[] = "S100010001000";
		while((SerialLib.good()) && (!bThreadStop))
		{
			while (SerialLib.rdbuf()->in_avail()) 
				SerialLib.get(cRxData[k++]);		

			if (*cRxData != '\0')
			{ // notify main thread that we got data 
				std::cout << "Received " << cRxData << '\n';

				*cRxData = '\0'; // Reset the data 
				k=0;
			}
			while (k1 < 14)
				SerialLib.put(cTxData[k1++]);
			k1 = 0;
			std::this_thread::sleep_for((std::chrono::milliseconds) 10); 
		}
		if (!SerialLib.good())
			std::cerr << "SerialStream broke, bye bye\n";
		else
			std::cerr << "Thread Stopped, bye bye\n";

	}
	catch(std::exception e)
	{
		std::cout << "Exception@ SerialCommunication(): " << e.what() << '\n';
	}
	catch(...)
	{
		std::cout << "Exception@ SerialCommunication()"<< '\n';
	}
}

// TODO: make send function
