#include "../include/Odroid.h"

extern char gcXmegaDataTx;
extern char gcXmegaDataRx;
extern char gcXbeeDataTx;
extern char gcXbeeDataRx;

extern std::atomic_bool gbXmegaData;
extern std::atomic_bool gbXbeeData;
extern std::mutex mMutex;

static int SerialInit(LibSerial::SerialStream& S, const char *pDevice);

int SerialXmegaCommunication(const char *pDevice)
{
	try
	{
		//std::cout << "define __linux__ = " << __linux__ << "\n";
		//std::cout << "define __MAX_BAUD = " << __MAX_BAUD << "\n";
		// std::cout << "323 && 0xF00 = " <<std::setbase(16) << (323 & 0xf00) << "\n";
		//std::cout << "123 && 0xFF = " << std::setbase(16) << (123 & 0xff) << "\n";
		// std::cout << "-3 << 4 = " << std::setbase(16) << (-3 << 4) << "\n";

		
		LibSerial::SerialStream S;
		int k;
		if ((k = SerialInit(S, pDevice)) != RET_SUCCESS)
		{
			;// TODO: cry why we failed
		}

		sleep(1); // Give time to atxmega to boot

		// if (PrintMsg("Setup Complete", "Xmega") != RET_SUCCESS)
			// exit(EXIT_FAILURE);
		PrintMsg("Setup Complete", "Xmega");
			
		char cByte[128], cRead, *pRead = cByte;
		// char cRead;
		while(S.good())
		{
			while (S.rdbuf()->in_avail()) 
			{
				S.get(cRead);		
				PrintMsg("Received: " + cRead, "Xmega Thread");
				gcXbeeDataRx = cRead;
				gbXmegaData = true;
			}
			S.write("8", sizeof("8"));
			usleep(100000); // 100ms 
		}
		std::cerr << "SerialStream broke, bye bye\n";
		return 8;
	}
	catch(std::exception e)
	{
		std::cerr << "Exception " << e.what() << std::endl;
	}
}

static int SerialInit(LibSerial::SerialStream& S, const char *pDevice)
{
	if (pDevice == nullptr)
		return -1;

	S.Open(pDevice);

	// TODO: substiture exits for returns
	if (S.good()) // Set baudrate 
		S.SetBaudRate(LibSerial::SerialStreamBuf::BAUD_115200);
	else
	{
		std::cerr << "Failed to Open " << *pDevice << std::endl;
		exit(-1);
	}

	if (S.good()) // Set Char size 
		S.SetCharSize( LibSerial::SerialStreamBuf::CHAR_SIZE_8 ) ;
		else
	{
		std::cerr << "Failed to set BAUD_115200" << std::endl;
		exit(-1);
	}

	if (S.good()) // Set Char size 
		S.SetParity(LibSerial::SerialStreamBuf::PARITY_NONE);
		else
	{
		std::cerr << "Failed to set CHAR_SIZE_8" << std::endl;
		exit(-1);
	}

	if (S.good()) // Set Char size 
		S.SetFlowControl(LibSerial::SerialStreamBuf::FLOW_CONTROL_NONE);
		else
	{
		std::cerr << "Failed to set PARITY_NONE" << std::endl;
		exit(-1);
	}

	return RET_SUCCESS;
}

