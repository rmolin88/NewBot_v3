/*
	libxbee - a C/C++ library to aid the use of Digi's XBee wireless modules
	          running in API mode.

	Copyright (C) 2009 onwards  Attie Grande (attie@attie.co.uk)

	libxbee is free software: you can redistribute it and/or modify it
	under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	libxbee is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with libxbee. If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <string.h>
#include <unistd.h>

#include <xbeep.h>

class myConnection: public libxbee::ConCallback {
	public:
		explicit myConnection(libxbee::XBee &parent, std::string type, struct xbee_conAddress *address = NULL): libxbee::ConCallback(parent, type, address) {};
		void xbee_conCallback(libxbee::Pkt **pkt);
		std::string myData;
};

void myConnection::xbee_conCallback(libxbee::Pkt **pkt) {
	std::cout << "Callback!!\n";
	int i;
	for (i = 0; i < (*pkt)->size(); i++) {
		std::cout << (**pkt)[i];
	}
	std::cout << "\n";

	std::cout << myData;
	std::cout << "\n";
	std::cout << "Got the data\n";

	/* if you want to keep the packet, then you MUST do the following:
	      libxbee::Pkt *myhandle = *pkt;
	      *pkt = NULL;
	   and then later, you MUST delete the packet to free up the memory:
	      delete myhandle;

	   if you do not want to keep the packet, then just leave everything as-is, and it will be free'd for you */
}


int main(int argc, char *argv[]) {
	try 
	{
		/* setup libxbee */
		libxbee::XBee xbee("xbee1", "/dev/ttyUSB1", 115200);

		std::cout << "Running libxbee in mode '" << xbee.mode() << "'\n";
		xbee.mode();

		/* make a connection */
		myConnection con(xbee, "Local AT"); /* with a callback */
		con.myData = "Testing, 1... 2... 3...\n";

		/* send data */
		//con.Tx("NI"); /* like this */
		con << "NI";    /* or like this */

		/* NOTE: if you're trying to set a configuration option, then you'll need to provide
		         the RAW value, not the ASCII character. To do this, see the following example:
		             con << "D4" + std::string(1, 0x05);
		         where "D4" will query or set the configuration of pin 4, and 0x05 will set it
		         to be an output, with a logic 'high' value

		         this is the C++ equivelant to calling the following from C:
		             xbee_conTx(con, NULL, "D4%c", 0x05);                                      */

		usleep(1000000);


		libxbee::Pkt pkt;

		try 
		{
			//con >> pkt; /* like this */
			pkt << con;   /* or this */
		} 
		catch (xbee_err err) 
		{
			std::cout << "Error on Rx! " << err << "\n";
			return 1;
		}

		try 
		{
			std::cout << "Packet length: " << pkt.size() << "\n";
			for (int i = 0; i < pkt.size(); i++) 
				std::cout << "  " << i << " " << pkt[i] << "\n";
		} 
		catch (xbee_err err) 
		{
			std::cout << "Error accessing packet! " << err << "\n";
			return 1;
		}

		usleep(1000000);
	} 
	catch (xbee_err err) 
	{
		std::cout << "Error " << err << "\n";
		char cMsgErr[256];
		strcpy(cMsgErr,xbee_errorToStr(err));
		std::cout << cMsgErr << std::endl;
	}
	
	return 0;
}
