#include "../include/Odroid.h"

#define LOOP_FREQ_AU_MS 100 // For Autonomous Mode 
#define LOOP_FREQ_RM_MS 20 // For Remote Control Mode 

// TODO: Make a robot class containing all this stuff
// 			- make this class granular not so extensive with other little classes
// TODO: implement serial communication protocol
// 		- first thing returned from serial should ID
// 		- something like x for xmega and b for xbee
// 		- implement it so that you can request ID from serial
// 		- like implement a series of CMD that you can issue to serial
// 		- like send me ID, use this PWM and stuff like that
// 		- The rate should also be dependant on the mode 
// 		- which should be part of the CMD like go into Remote Control Mode
// TODO: Push serial communication to its limits see how low you can get
//

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

	if (argc < 3)
	{
		//TODO: 
		std::cout << "Bad Usage" << std::endl;
		exit(EXIT_FAILURE);
	}
	// TODO: strip xmega=
	int k;
	LibSerial::SerialStream lserialXmega, lserialXbee;

	if ((k = SerialInit(lserialXmega, argv[1])) != RET_SUCCESS)
	{
		std::cout << "SerialInit() Error: " << k << " on device :" << argv[1] << '\n';
		exit(EXIT_FAILURE);
	}

	if ((k = SerialInit(lserialXbee, argv[2])) != RET_SUCCESS)
	{
		std::cout << "SerialInit() Error: " << k << " on device :" << argv[2] << '\n';
		exit(EXIT_FAILURE);
	}

	PrintMsg("Serial Setup Complete", "Main Thread");

	gbXmegaData = false;
	gbXbeeData = false;
	std::thread tSerialXmega(SerialCommunication, std::ref(lserialXmega));
	// std::thread tSerialXbee(SerialInitXbee);
	// std::thread tImageProcessing(InitCamera);

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	std::chrono::duration<double, std::milli> diff;
	// std::chrono::duration<double> diff;

	char buff[CHAR_SIZE] = {0};
	while (1) // Threads are alive
	{
		start = std::chrono::system_clock::now();
		if (gbXmegaData) // Do xmega processing
		{
			std::sprintf(buff,"Xmega Received: %s", gcXmegaDataRx);
			PrintMsg(buff , "Main Thread");
			// printf("%d %d\n", gcXmegaDataRx[0], gcXmegaDataRx[1]);
			gbXmegaData = false;
		}

		if (gbXbeeData) // Do xbee processing
		{
			std::sprintf(buff,"Xbee Received: %s", gcXbeeDataRx);
			PrintMsg(buff , "Main Thread");
			// printf("%d %d\n", gcXbeeDataRx[0], gcXbeeDataRx[1]);
			gbXbeeData = false;
		}

		// wait to loop
		// TODO: make this a function
		diff = end - start;
		while (diff.count() < LOOP_FREQ_MS)
		{
			end = std::chrono::system_clock::now();
			diff = end - start;
			usleep(1000); // Do not use so many resources
		}
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

