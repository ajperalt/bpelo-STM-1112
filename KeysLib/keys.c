#include <string.h>
#include <stdio.h>

#include "../includes/io/sapim_io.h"
#include "../includes/keys/sapim_keys_errors.h"
#include "../includes/keys/sapim_keys_functions.h"
#include "ssmkeys.h"

#define ARRAY_KEYS {GPIO_UP,GPIO_RIGHT, GPIO_DOWN, GPIO_LEFT, GPIO_OK}

void keysSetLastError(char* str);

int keys[KEY_COUNT];
int gpioNumbers[KEY_COUNT] = ARRAY_KEYS;

char keysLastError[101] = { 0 };

void keysSetLastError(char* str) {
	strncpy(keysLastError, str, 100);
	keysLastError[100] = '\0';
}

char* keysGetLastError() {
	return keysLastError;
}

int keysInit() {
	int err;
	int i;
	char tmp[100];

	for (i = 0; i < KEY_COUNT; i++) {
		err = ioCreate(gpioNumbers[i]);
		if (err < 0) {
			sprintf(tmp, "Couldn't create the gpio%d!", gpioNumbers[i]);
			keysSetLastError(tmp);
			return (err);
		}
		err = ioSetDirection(gpioNumbers[i], "in");
		if (err < 0) {
			sprintf(tmp, "Couldn't set the direction of gpio%d!",
					gpioNumbers[i]);
			keysSetLastError(tmp);
			return (err);
		}
		err = ioSetActiveLow(gpioNumbers[i], 1);
		if (err < 0) {
			sprintf(tmp, "Couldn't set active_low of gpio%d!", gpioNumbers[i]);
			keysSetLastError(tmp);
			return (err);
		}
	}
	return 0;
}

int* keysGetAll(int* length) {
	if (length != 0) {
		*length = KEY_COUNT;
	}

	return keys;
}

int keysGetLeft() {
	return (keys[KEY_LEFT] > 0 ? KEYS_TRUE : KEYS_FALSE);
}

int keysGetRight() {
	return (keys[KEY_RIGHT] > 0 ? KEYS_TRUE : KEYS_FALSE);
}

int keysGetUp() {
	return (keys[KEY_UP] > 0 ? KEYS_TRUE : KEYS_FALSE);
}

int keysGetDown() {
	return (keys[KEY_DOWN] > 0 ? KEYS_TRUE : KEYS_FALSE);
}

int keysGetEnter() {
	return (keys[KEY_OK] > 0 ? KEYS_TRUE : KEYS_FALSE);
}

int keysWaitOnPress() {
	int ret = 0;
	while ((ret = keysRefresh()) == KEYS_STATE_UNCHANGED)
		;
	return ret;
}

int keysRefresh() {
	int i;
	int value;
	int ret = KEYS_STATE_UNCHANGED;
	char tmp[100];

	for (i = 0; i < KEY_COUNT; i++) {
		value = ioGetValue(gpioNumbers[i]);
		if (value < 0) {
			sprintf(tmp, "Couldn't get the value of gpio%d!", gpioNumbers[i]);
			keysSetLastError(tmp);
			return value;
		}
		if (keys[i] == 0 && value != keys[i]) {
			ret = KEYS_STATE_CHANGED;
		}
		keys[i] = value;
	}

	return ret;
}

void keysClear() {
	int i;
	for (i = 0; i < KEY_COUNT; i++) {
		keys[i] = 0;
	}
}
