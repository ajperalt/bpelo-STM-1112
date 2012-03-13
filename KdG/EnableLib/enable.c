
#include <string.h>
#include "../includes/io/sapim_io.h"
#include "../includes/enable/sapim_enable_errors.h"
#include "enable.h"

char enableLastError[101] = { 0 };

void enableSetLastError(char* str) {
	strncpy(enableLastError, str, 100);
	enableLastError[100] = '\0';
}

char* enableGetLastError() {
	return enableLastError;
}

int enableInit(int number, char* direction, int active_low, int active) {
    int err;
    err = ioCreate(number);
    if (err != IO_SUCCESS)  {
    	enableSetLastError("Coudln't create the io!");
        return err;
    }
    err = ioSetDirection(number, direction);
    if (err != IO_SUCCESS)  {
    	enableSetLastError("Coudln't set the direction!");
        return err;
    }
    err = ioSetActiveLow(number, active_low);
    if (err != IO_SUCCESS)  {
    	enableSetLastError("Couldn't set active_low!");
        return err;
    }
    err = ioSetValue(number, active);
    if (err != IO_SUCCESS)  {
    	enableSetLastError("Coudln't set the value!");
        return err;
    }

    return ENABLE_SUCCESS;
}

int enable(int number) {
    int err;
    err = ioSetValue(number, 1);
    return err;
}

int disable(int number) {
    int err;
    err = ioSetValue(number, 0);
    return err;
}

