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
		int iTxDataSize = sizeof(cTxData);

		while((SerialLib.good()) && (!bThreadStop))
		{  
			while (SerialLib.rdbuf()->in_avail()) 
				SerialLib.get(cRxData[k++]);		 // store data if available 

			if (*cRxData != '\0') // if we received some data 
			{ // notify main thread that we got data 
				std::cout << "Received " << cRxData << '\n'; // do something
				// with this data 
				*cRxData = '\0'; // Reset the data 
			}

			while (k1 < iTxDataSize) // send data 
			{
				SerialLib.put(cTxData[k1++]); // give the buffer some time
				// std::this_thread::sleep_for((std::chrono::nanoseconds) 488); 
			}
			// SerialLib.write(cTxData, iTxDataSize);
			// SerialLib << 'S';
			// SerialLib << 1000;
			// SerialLib << 1000;
			// SerialLib << 1000;
			// SerialLib << '\\';

			k1 = k = 0; // Reset iterators 
			// sleep for now 
			std::this_thread::sleep_for((std::chrono::milliseconds) 100); 
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
