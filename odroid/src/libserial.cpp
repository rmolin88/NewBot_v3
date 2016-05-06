#include <iostream>
#include <iomanip>
#include <SerialStream.h>

#define RET_SUCCESS 0

int SerialInit(LibSerial::SerialStream& S, const char *pDevice);
int ParseSerialDataRecvd(const char *pData);

int main ( int argc, char **argv ) 
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
		if ((k = SerialInit(S, "/dev/ttyUSB0")) != RET_SUCCESS)
		{
			;// TODO: cry why we failed
		}

		sleep(1); // Give time to atxmega to boot
		std::cout << "Setup complete" << std::endl;

		char cByte[128], cRead, *pRead = cByte;
		// char cRead;
		while(S.good())
		{
			while (S.rdbuf()->in_avail()) 
			{
				S.get(cRead);		
				// S.read(pRead, sizeof(cByte));		
				std::cout << "Received: " << cRead << "\n";
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

int SerialInit(LibSerial::SerialStream& S, const char *pDevice)
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

int ParseSerialDataRecvd(const char *pData)
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
