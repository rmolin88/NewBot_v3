#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "../../odroid/include/SerialXmega.h"

#define DEVICE "/dev/ttyUSB0"

class BufferToggle
{
    private:
        struct termios t;

    public:
        // Disables buffered input
        void off(void)
        {
            tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
            t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
			tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
        }

        // Enables buffered input
        void on(void)
        {
            tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
            t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
			tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
        }
};

int main(int argc, char **argv)
{
	int k;
	char cCh=0;
	BufferToggle ToggleBuffer;
	LibSerial::SerialStream lserialXbee;

	if ((k = SerialInit(lserialXbee, DEVICE)) != RET_SUCCESS)
	{
		std::cout << "SerialInit() Error: " << k << " on device :" << DEVICE << '\n';
		exit(EXIT_FAILURE);
	}


	ToggleBuffer.off();

	while (cCh != 'q')
	{
		std::cin.get(cCh);
		std::cout << "My remote got: " << cCh << '\n';
	}
	std::cout << "Done" << std::endl;

	exit(EXIT_SUCCESS);
}
