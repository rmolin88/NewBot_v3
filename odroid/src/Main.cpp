#include "../include/Odroid.h"

#define CHAR_SIZE 32
char gcXmegaDataTx[CHAR_SIZE] = {0};
char gcXmegaDataRx[CHAR_SIZE] = {0};
char gcXbeeDataTx[CHAR_SIZE] = {0};
char gcXbeeDataRx[CHAR_SIZE] = {0};

std::atomic_bool gbXmegaData;
std::atomic_bool gbXbeeData;
std::mutex mMutex;

static int ParseSerialDataRecvd(const char *pData);

// Odroid
int main ( int argc, char **argv ) 
{
	
	std::thread tSerialXmega(SerialXmegaCommunication,"/dev/ttyUSB0");
	// std::thread tSerialXbee(SerialInitXbee);
	// std::thread tImageProcessing(InitCamera);

	char buff[CHAR_SIZE] = {0};
	while (1)
	{
		if (gbXmegaData) 
		{
			// Do xmega processing
			std::sprintf(buff,"Received: %s", gcXbeeDataRx);
			PrintMsg(buff , "Main Thread: ");
			gbXmegaData = false;
		}

		if (gbXbeeData) 
			; // Do xbee processing
	}
}

static int ParseSerialDataRecvd(const char *pData)
{
	if (pData == nullptr)
		return -1;

	int leftSonar,centerSonar,rightSonar;
	for ( int i = 0; i<4; i++ ) 
	{
		switch ( i ) 
		{
			case 0:
				leftSonar += ( pData[0] - '0' ) *1000;
				centerSonar += ( pData[4] - '0' ) *1000;
				rightSonar += ( pData[8] - '0' ) *1000;
				break;
			case 1:
				leftSonar += ( pData[1] - '0' ) *100;
				centerSonar += ( pData[5] - '0' ) *100;
				rightSonar += ( pData[9] - '0' ) *100;
				break;
			case 2:
				leftSonar += ( pData[2] - '0' ) *10;
				centerSonar += ( pData[6] - '0' ) *10;
				rightSonar += ( pData[10] - '0' ) *10;
				break;
			case 3:
				leftSonar += ( pData[3] - '0' );
				centerSonar += ( pData[7] - '0' );
				rightSonar += ( pData[11] - '0' );
				break;
		}
	}
	return RET_SUCCESS;
}

int PrintMsg(const char *pMsg, const char *pThreadName)
{
	try
	{
		if ((!pMsg) || (!pThreadName))
			return -1;

		std::lock_guard<std::mutex> guard(mMutex);
		std::cout << pThreadName << " says: " << pMsg << "\n";
		return RET_SUCCESS;
	}
	catch(std::exception e)
	{
		std::cout << "PrintMsg() Exception: " << e.what() << "\n";
		return -100;
	}
}

