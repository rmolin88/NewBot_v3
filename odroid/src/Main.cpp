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

static int ParseSerialDataRecvd(const char *pData);
static std::atomic_flag lock = ATOMIC_FLAG_INIT;

// Odroid
int main ( int argc, char **argv ) 
{
	try 
	{
		if (argc < 3)
		{
			//TODO: 
			std::cout << "Bad Usage" << '\n';
			exit(EXIT_FAILURE);
		}
		// TODO: strip xmega= from input argv
		CustSerial Xmega(argv[1], BAUD);

		PrintMsg("Serial Setup Complete", "Main Thread");

		std::chrono::system_clock::time_point start;
		std::chrono::system_clock::time_point end;
		std::chrono::duration<double, std::milli> diff;
		int k=0;

		while (1) // Threads are alive
		{
			start = std::chrono::system_clock::now();
			// PrintMsg("Looping", "Main Thread");
			// wait to loop
			// TODO: make this a function
			diff = end - start;
			while (diff.count() < LOOP_FREQ_AU_MS)
			{
				end = std::chrono::system_clock::now();
				diff = end - start;
				std::this_thread::sleep_for((std::chrono::duration<int, std::milli>) 1);
			}
			if (k == 150)
			{
				PrintMsg("Stopped Program", "Main Thread");
				Xmega.bThreadStop = true;
				break;
			}
			else
			{
				// std::cout << k << '\n';
				k++;
			}
		}
	}
	catch(std::exception e)
	{
		std::cout << "Main() Exception: " << e.what() << "\n";
		return -100;
	}
}

// TODO: send serial data functions

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

int PrintMsg(const std::string& sMsg, const std::string& sThreadName)
{
	try
	{
		while (lock.test_and_set(std::memory_order_acquire))  // acquire lock
			; // spin
		std::cout << sThreadName << " says: " << sMsg << '\n';
		lock.clear(std::memory_order_release);               // release lock
		return RET_SUCCESS;
	}
	catch(std::exception e)
	{
		std::cout << "PrintMsg() Exception: " << e.what() << "\n";
		return -100;
	}
}



