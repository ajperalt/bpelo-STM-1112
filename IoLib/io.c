#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/io/sapim_io_errors.h"

char ioLastError[101] = { 0 };

void ioSetLastError(char* str) {
	strncpy(ioLastError, str, 99);
	ioLastError[100] = '\0';
}

char* ioGetLastError() {
	return ioLastError;
}

int ioCreate(int number) {
    char path[255];
    char value[10];
    FILE *file = NULL;
    size_t ret;

    sprintf(path, "/sys/class/gpio/export");
    sprintf(value, "%d", number);

    file = fopen(path, "w");
    if(!file) {
    	ioSetLastError("Coudln't open the export file!");
        return IO_ERROR_OPEN;
    }

    ret = fwrite(value, sizeof(char), strlen(value), file);
    fclose(file);
    if(ret != strlen(value)) {
    	ioSetLastError("Coudln't write to the export file!");
        return IO_ERROR_WRITE;
    }

    return IO_SUCCESS;
}

int ioSetDirection(int number, char* direction) {
    char path[255];
    FILE* file = NULL;
    size_t ret;

    sprintf(path, "/sys/class/gpio/gpio%d/direction", number);

    file = fopen(path, "w");
    if(!file) {
    	ioSetLastError("Coudln't open the direction file!");
        return IO_ERROR_OPEN;
    }

    ret = fwrite(direction, sizeof(char), strlen(direction), file);
    fclose(file);
    if(ret != strlen(direction)) {
    	ioSetLastError("Coudln't write to the direction file!");
        return IO_ERROR_WRITE;
    }

    return IO_SUCCESS;
}

int ioSetActiveLow(int number, int value) {
    char path[255];
    char strValue[10];
    FILE *file = NULL;
    size_t ret;

    sprintf(path, "/sys/class/gpio/gpio%d/active_low", number);
    sprintf(strValue, "%d", value);

    file = fopen(path, "w");
    if(!file) {
    	ioSetLastError("Coudln't open the active_low file!");
        return IO_ERROR_OPEN;
    }

    ret = fwrite(strValue, sizeof(char), strlen(strValue), file);
    fclose(file);
    if(ret != strlen(strValue)) {
    	ioSetLastError("Coudln't write to the active_low file!");
        return IO_ERROR_WRITE;
    }

    return IO_SUCCESS;
}

int ioSetValue(int number, int value) {
    char path[255];
    char strValue[10];
    FILE *file = NULL;
    size_t ret;

    sprintf(path, "/sys/class/gpio/gpio%d/value", number);
    sprintf(strValue, "%d", value);

    file = fopen(path, "w");
    if(!file) {
    	ioSetLastError("Coudln't open the value file!");
        return IO_ERROR_OPEN;
    }

    ret = fwrite(strValue, sizeof(char), strlen(strValue), file);
    fclose(file);
    if(ret != strlen(strValue)) {
    	ioSetLastError("Coudln't write to the value file!");
        return IO_ERROR_WRITE;
    }

    return IO_SUCCESS;
}


int ioGetValue(int number) {
    char path[255];
    char value;
    FILE *file = NULL;
    size_t ret;

    sprintf(path, "/sys/class/gpio/gpio%d/value", number);

    file = fopen(path, "r");
    if(!file) {
    	ioSetLastError("Coudln't open the value file!");
        return IO_ERROR_OPEN;
    }
    ret = fread(&value,sizeof(char),1,file);
    fclose(file);
    if(ret != 1){
    	ioSetLastError("Coudln't read the value file!");
        return IO_ERROR_READ;
    }
    return(value - '0');
}



