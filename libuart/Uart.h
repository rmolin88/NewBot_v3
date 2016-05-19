#ifndef SERIAL_XMEGA_H_
#define SERIAL_XMEGA_H_

#include <iostream>
#include <thread>
#include <chrono>
#include <SerialStream.h>

#define RET_SUCCESS 0


class CustSerial {
	public:
		char cRxData[128];
		char cTxData[128];
		bool bRxDataRdy;
		bool bTxDataRdy;
		bool bDataProcessed;
		bool bThreadStop;
		std::thread tWorkerThread;
		LibSerial::SerialStream SerialLib;



		explicit CustSerial(char *pDevice, int iBaud):
			cRxData({0}),
			cTxData({0}),
			bRxDataRdy(false),
			bTxDataRdy(false),
			bDataProcessed(false),
			bThreadStop(false),
			tWorkerThread()
			{
				LibSerial::SerialStreamBuf::BaudRateEnum eBaud;
				switch (iBaud) 
				{
					case 9600:
						eBaud = LibSerial::SerialStreamBuf::BAUD_9600;
						break;
					case 115200:
						eBaud = LibSerial::SerialStreamBuf::BAUD_115200;
						break;
				}

				SerialLib.Open(pDevice);
				SerialLib.SetBaudRate(eBaud);

				if ((SerialLib.IsOpen()) && (SerialLib.good()))
					tWorkerThread = std::thread(&CustSerial::SerialCommunication, this);
				else
				{
					std::cout << "Error initializing " << pDevice << '\n';
					bThreadStop = true;
				}
			}

		~CustSerial()
		{
			bThreadStop = true;
			if (tWorkerThread.joinable())
				tWorkerThread.join();
		}

		void SerialCommunication();
}; 

#endif
