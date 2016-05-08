#include "../include/Odroid.h"

char gcXmegaDataTx[CHAR_SIZE] = {0};
char gcXmegaDataRx[CHAR_SIZE] = {0};
char gcXbeeDataTx[CHAR_SIZE] = {0};
char gcXbeeDataRx[CHAR_SIZE] = {0};

// std::atomic_char gcXmegaDataTx[CHAR_SIZE] = {0};
// std::atomic_char gcXmegaDataRx[CHAR_SIZE] = {0};
// std::atomic_char gcXbeeDataTx[CHAR_SIZE] = {0};
// std::atomic_char gcXbeeDataRx[CHAR_SIZE] = {0};

std::atomic_bool gbXmegaData;
std::atomic_bool gbXbeeData;
std::mutex mMutex;

static int ParseSerialDataRecvd(const char *pData);

// Odroid
int main ( int argc, char **argv ) 
{
	gbXmegaData = false;
	gbXbeeData = false;
	std::thread tSerialXmega(SerialXmegaCommunication,"/dev/ttyUSB1");
	// std::thread tSerialXbee(SerialInitXbee);
	// std::thread tImageProcessing(InitCamera);
	
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	std::chrono::duration<double, std::milli> diff;
	// std::chrono::duration<double> diff;
	
	char buff[CHAR_SIZE] = {0};
	while (1)
	{
		start = std::chrono::system_clock::now();
		if (gbXmegaData) // Do xmega processing
		{
			std::sprintf(buff,"Received: %s", gcXmegaDataRx);
			PrintMsg(buff , "Main Thread");
			printf("%d %d\n", gcXmegaDataRx[0], gcXmegaDataRx[1]);
			gbXmegaData = false;
		}

		if (gbXbeeData) // Do xbee processing
			; 

		// wait to loop
		// TODO: make this a function
		diff = end - start;
		while (diff.count() < 100)
		{
			end = std::chrono::system_clock::now();
			diff = end - start;
		}
		// std::cout << "loop time: "
					// << std::chrono::duration_cast<std::chrono::milliseconds>(
						// end.time_since_epoch()).count() 
					// << '\n';
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
		std::cout << pThreadName << " says: " << pMsg << '\n';
		return RET_SUCCESS;
	}
	catch(std::exception e)
	{
		std::cout << "PrintMsg() Exception: " << e.what() << "\n";
		return -100;
	}
}

