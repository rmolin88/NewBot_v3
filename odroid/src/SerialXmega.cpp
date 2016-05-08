#include "../include/Odroid.h"

extern char gcXmegaDataTx[CHAR_SIZE];
extern char gcXmegaDataRx[CHAR_SIZE];
extern char gcXbeeDataTx[CHAR_SIZE];
extern char gcXbeeDataRx[CHAR_SIZE];

extern std::atomic_bool gbXmegaData;
extern std::atomic_bool gbXbeeData;
extern std::mutex mMutex;

static int SerialInit(LibSerial::SerialStream& S, const char *pDevice);

int SerialXmegaCommunication(const char *pDevice)
{
	try
	{
		int k;
		char cMsgErr[32];
		LibSerial::SerialStream S;

		if ((k = SerialInit(S, pDevice)) != RET_SUCCESS)
		{
			std::sprintf(cMsgErr, "SerialInit() Error: %d", k);
			PrintMsg(cMsgErr, "Xmega Thread");
			return -100;
		}

		PrintMsg("Setup Complete", "Xmega Thread");

		sleep(1); // Give time to atxmega to boot

		char *pRxData = gcXmegaDataRx;
		while(S.good())
		{
			while (S.rdbuf()->in_avail()) 
			{
				S.get(*pRxData);		
				pRxData++;
				gbXmegaData = true;
			}
			S.write("8", sizeof("8"));
			usleep(80000); // 100ms 
		}
		std::cerr << "SerialStream broke, bye bye\n";
		return 8;
	}
	catch(std::exception e)
	{
		std::cerr << "Exception " << e.what() << std::endl;
		return -100;
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

