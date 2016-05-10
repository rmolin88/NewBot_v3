#include <iostream>
#include <termios.h>
#include <unistd.h>

// E153 deck 7 - Reservation - 382530
// june 25 - 27
// me passport, resident and id

class BufferToggle
{
    private:
        struct termios t;

    public:
        /*
         * Disables buffered input
         */
        void off(void)
        {
            tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
            t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
			tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
        }

        /*
         * Enables buffered input
         */
        void on(void)
        {
            tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
            t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
			tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
        }
};

int main(int argc, char **argv)
{
	char cCh=0;
	BufferToggle ToggleBuffer;
	ToggleBuffer.off();

	while (cCh != 'q')
	{
		std::cin.get(cCh);
		std::cout << "My remote got: " << cCh << '\n';
	}
	std::cout << "Done" << std::endl;

	exit(EXIT_SUCCESS);
}
