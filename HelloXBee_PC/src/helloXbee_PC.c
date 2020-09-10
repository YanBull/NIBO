/**
 *\author Felix Hahn
 *\date 02.10.2014
 *\version 1.0
 *\brief This Program can be used to test the XBEE communication between two a Nibo and a PC via serial communication.
 *\It receives the incoming chars on the selected serial port and send the chars you type in into the console to the nibo.
 *\The serial port is configured to work with 9600 bit/s with 8N1! This is the default setting for the xbee modules!
 */


//includes
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

//define the serial port you want to use -> to get the serial portin which your XBEE adapter is connected type ls /dev/ttyUSB* in a terminal
#define dev "/dev/ttyUSB0"

int main(void)
{

	struct termios old_termios;
	struct termios new_termios;
	//buffer to save the chars
	char buf[4];
	//pointed on the opened serial device
	int fd;
	//to save the count of chars received
	int res;
	//to save the chars which are typed into the console
	char ch;

	//opens the serial port
	fd = open(dev, O_RDWR | O_NOCTTY);
	//if the selected serial port is not found
	if (fd < 0) {
		fprintf(stderr, "error, counldn't open file %s\n", dev);
		return 1;
	}
	//returns an integer that either indicates success or failure of the prot opening
	if (tcgetattr(fd, &old_termios) != 0) {
		fprintf(stderr, "tcgetattr(fd, &old_termios) failed: %s\n", strerror(errno));
		return 1;
	}
	//configure the serial port -> for more information: http://en.wikibooks.org/wiki/Serial_Programming/termios
	memset(&new_termios, 0, sizeof(new_termios));
	new_termios.c_iflag = IGNPAR; //ignore parity bit
	new_termios.c_oflag = 0;
	new_termios.c_cflag = CS8 | CREAD | CLOCAL | HUPCL; //sets the serial port to 8N1
	new_termios.c_lflag = 0;
	new_termios.c_cc[VINTR]    = 0;
	new_termios.c_cc[VQUIT]    = 0;
	new_termios.c_cc[VERASE]   = 0;
	new_termios.c_cc[VKILL]    = 0;
	new_termios.c_cc[VEOF]     = 4;
	new_termios.c_cc[VTIME]    = 0;
	new_termios.c_cc[VMIN]     = 1;
	new_termios.c_cc[VSWTC]    = 0;
	new_termios.c_cc[VSTART]   = 0;
	new_termios.c_cc[VSTOP]    = 0;
	new_termios.c_cc[VSUSP]    = 0;
	new_termios.c_cc[VEOL]     = 0;
	new_termios.c_cc[VREPRINT] = 0;
	new_termios.c_cc[VDISCARD] = 0;
	new_termios.c_cc[VWERASE]  = 0;
	new_termios.c_cc[VLNEXT]   = 0;
	new_termios.c_cc[VEOL2]    = 0;
	//sets the input speed of the serial interdace to 9600baud
	if (cfsetispeed(&new_termios, B9600) != 0) {
		fprintf(stderr, "cfsetispeed(&new_termios, B9600) failed: %s\n", strerror(errno));
		return 1;
	}
	//sets the output speed of the serial interdace to 9600baud
	if (cfsetospeed(&new_termios, B9600) != 0) {
		fprintf(stderr, "cfsetospeed(&new_termios, B9600) failed: %s\n", strerror(errno));
		return 1;
	}
	//sets the termios struct of the file handle fd from the options defined via the options
	if (tcsetattr(fd, TCSANOW, &new_termios) != 0) {
		fprintf(stderr, "tcsetattr(fd, TCSANOW, &new_termios) failed: %s\n", strerror(errno));
		return 1;
	}



	//Now read() and write() to the device at your heart's delight
	//loop until you type an x
	while ((ch=fgetc(stdin))!='x') {
		//catches the pressed return to confirm the console input
		if(ch!='\n'){
			//sends the chars which are typed into the console
			write(fd, &ch , 1);
			//read the incoming chars into the buffer
			res = read(fd,buf,1);
			//get the first char of the buffer
			buf[res]=0;
			//print the first char with the length of the buffer.
			printf("%s, length %d\n", buf, res);
		}

	}


	// Before leaving, reset the old serial settings and close the serial port
	tcsetattr(fd, TCSANOW, &old_termios);
	close(fd);
	printf("Serial port closed");
	return 0;
}
