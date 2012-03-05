/*
 * serial.c
 *
 *  Created on: May 4, 2011
 *      Author: philip
 */

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "serial.h"
#include "../includes/serial/sapim_serial_all.h"

/*
 * private functions
 */
int serialOpenPort();
int serialInitLocalPort(int baudrateIn, int baudrateOut);

/*
 * private variables
 */
int flags = 0;
int fdPort = 0;
struct termios standardOptions;

int serialInitPort() {
	int ret;
	char autoBaud = 0x55;

#if DEBUG > 1
	printf("Debug: initPort()\n");
#endif
	if ((flags & SERIAL_FLAG_OPENED) != 0) {
#if DEBUG > 1
		printf("Debug: Port is already opened!\n");
#endif
		return SERIAL_PORT_ALREADY_OPENED;
	}

	ret = serialOpenPort();
	if (ret != SERIAL_SUCCESS) {
		return SERIAL_ERROR;
	}

	ret = serialInitLocalPort(BAUDRATE_9600, BAUDRATE_9600);
	if (ret != SERIAL_SUCCESS) {
		return SERIAL_LOCAL_ERROR;
	}

#if DEBUG > 1
	printf("Debug: Sending auto baud command\n");
#endif

	ret = serialWriteData(&autoBaud, 1, 1);
	if (ret != SERIAL_SUCCESS) {
#ifdef DEBUG
		printf("Error: Autobaud command error\n");
#endif
		return SERIAL_ERROR;
	} else {
#if DEBUG > 1
		printf("Debug: Autobaud success\n");
#endif
		return SERIAL_SUCCESS;
	}
}

int serialOpenPort() {
#if DEBUG > 1
	printf("Debug: Opening port: %s\n", PORTNAME);
#endif
	fdPort = open(PORTNAME, O_RDWR /* | O_FSYNC */);
	if (fdPort < 0) {
#ifdef DEBUG
		printf("Error: Couldn't open the port!\n");
#endif
		return SERIAL_ERROR;
	}
#if DEBUG > 1
	printf("Debug: Port opened!\n");
#endif

	tcgetattr(fdPort, &standardOptions);
	return SERIAL_SUCCESS;
}

int serialChangeBaudRate(int baudrate) {
	char cmd[2];

#if DEBUG > 1
	printf("Debug: Changing baudrate to %d\n", baudrate);
#endif

	cmd[0] = 0x51;
	switch (baudrate) {
	case BAUDRATE_9600:
		cmd[1] = 0x06;
		break;
	case BAUDRATE_19200:
		cmd[1] = 0x08;
		break;
	case BAUDRATE_115200:
		cmd[1] = 0x0D;
		break;
	default:
#ifdef DEBUG
		printf("Error: Undefined baudrate! 9600 used instead!\n");
#endif
		cmd[1] = 0x06;
		baudrate = BAUDRATE_9600;
	}

	if (serialInitLocalPort(baudrate, 0) != SERIAL_SUCCESS) {
		return SERIAL_ERROR;
	}

	if (serialWriteData(cmd, 2, 1) != SERIAL_SUCCESS) {
#ifdef DEBUG
		printf("Error: Couldn't change de baudrate on the LCD\n");
#endif
		// return SERIAL_ERROR;
	}

#if DEBUG > 1
	printf("Debug: LCD baudrate changed\n");
#endif

	if (serialInitLocalPort(baudrate, baudrate) != SERIAL_SUCCESS) {
		return SERIAL_ERROR;
	}

#if DEBUG > 1
	printf("Debug: Output baudrate changed\n");
#endif

	return SERIAL_SUCCESS;
}

int serialInitLocalPort(int baudrateIn, int baudrateOut) {
	//Configure serial port
	struct termios options;

#if DEBUG > 1
	printf("Debug: init local port; in: %d; out: %d\n", baudrateIn, baudrateOut);
#endif

	//call blockinfdPortg behaviour
	fcntl(fdPort, F_SETFL, 0);
	tcgetattr(fdPort, &options);
	if (baudrateIn != 0) {
		cfsetispeed(&options, baudrateIn);
	}

	if (baudrateOut != 0) {
		cfsetospeed(&options, baudrateOut);
	}
	options.c_cflag &= ~PARENB; //geen pariteit
	options.c_cflag &= ~CSTOPB; //geen pariteit
	options.c_cflag &= ~CSIZE; //mask char size bits
	options.c_cflag |= CS8; //8data bits
	options.c_lflag &= ~(ICANON | ECHO | ISIG);
	options.c_oflag &= ~OPOST;

	options.c_cc[VMIN] = 1; //min # of chars to read
	options.c_cc[VTIME] = 1; //# of tenths of seconds to wait for VMIN # of bytes to be read

	if (tcsetattr(fdPort, TCSANOW, &options) != 0) {
#ifdef DEBUG
		printf("Error: Couldn't change the options for local port!\n");
#endif
		return SERIAL_ERROR;
	}
#if DEBUG > 1
	printf("Debug: local change success\n");
#endif
	return SERIAL_SUCCESS;
}

int serialWriteData(const char* cmd, int length, char waitForResponse) {
	int i;
	int tries = 1;
	int success;
	char buff[10];

	do {
		success = 1;
#if DEBUG > 1
		printf("Debug: Sending data, tries: %d\n", tries);
		printf("Data: ");
#endif

		for (i = 0; i < length && success == 1; i++) {
#if DEBUG > 1
			printf(" %02X", cmd[i]);
#endif
			if (write(fdPort, &cmd[i], 1) != 1) {
#ifdef DEBUG
				printf("\nError: Couldn't write the data!\n");
#endif
				success = 0;
			}
		}

		tries--;
	} while (tries > 0 && success == 0);

	if (success == 0) {
#ifdef DEBUG
		printf("Error: Couldn't write data!\n");
#endif
		return SERIAL_ERROR;
	} else {

#ifdef DEBUG
		printf("\nDebug: Write success\n");
#endif
		if (waitForResponse == SERIAL_TRUE) {
#if DEBUG > 1
			printf("Debug: Waiting for response!\n");
#endif
			if (serialReadData(buff, 10) != 1 && buff[0] != ACK) {
#ifdef DEBUG
				printf("Error: Response != ACK\n");
#endif
				return SERIAL_ERROR;
			} else {
#if DEBUG > 1
				printf("Debug: Response == ACK\n");
#endif
				return SERIAL_SUCCESS;
			}
		} else {
			return SERIAL_SUCCESS;
		}
	}
}

int serialReadData(char* buff, int length) {
	int ret;
#if DEBUG > 1
	int i;
#endif

#if DEBUG > 1
	printf("Debug: reading data\n");
#endif
	ret = read(fdPort, buff, length);
	if (ret < 0) {
#ifdef DEBUG
		printf("Error: Reading data; ret: %d; length: %d\n", ret, length);
#endif
		return SERIAL_ERROR;
	} else if (ret == 0) {
#ifdef DEBUG
		printf("Error: Reading: end of file\n");
#endif
		return SERIAL_ERROR;
	} else {
#if DEBUG > 1
		printf("Debug: data read; ret: %d, length: %d\n", ret, length);
		printf("Data:");
		for (i = 0; i < ret; i++) {
			printf(" %02X", buff[i]);
		}
		printf("\n");
#endif
		return SERIAL_SUCCESS;
	}
}
