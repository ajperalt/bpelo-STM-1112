/*
 * container.c
 *
 *  Created on: May 7, 2011
 *      Author: philip
 */

#include <string.h>
#include <stdlib.h>

#ifdef DEBUG_CONTAINER
#include <stdio.h>
void dispContainer();
#endif

#include "../../includes/gui/sapim_gui_all.h"
#include "../structs.h"

#include "container.h"

void containerPrivateAddComponent(CONTAINER_ELEMENT *array,
		COMPONENT *component);
void expandArray();
unsigned int containerCalculateHashCode(char* component);

CONTAINER_ELEMENT *components = 0;
int size = 0;
int used = 0;
int iterator;

void containerAddComponent(COMPONENT* component) {
	if (used == size) {
		expandArray();
	}

#if DEBUG_CONTAINER > 1
	printf("Container: Add component %X; name: %s\n", (unsigned int) component,
			((BASE_COMPONENT*) component)->id.name);
	fflush(stdout);
#endif

	containerPrivateAddComponent(components, component);
	used++;

#if DEBUG_CONTAINER > 1
	dispContainer();
#endif
}

COMPONENT* containerRemoveComponent(char* name) {
	unsigned int code = containerCalculateHashCode(name) % size;
	unsigned int start = code;
	BASE_COMPONENT *base = 0;
	CONTAINER_ELEMENT *element;

#if DEBUG_CONTAINER > 1
	printf("Container: Removing component %s\n", name);
	fflush(stdout);
#endif

	do {
		element = &components[code++];
		base = (BASE_COMPONENT*) element->component;

		if (code == size) {
			code = 0;
		}

	} while (code != start && (element->isRemoved == GUI_TRUE || (base != 0
			&& strcmp(base->id.name, name) != 0)));
#if DEBUG_CONTAINER > 1
	printf("Container: while end code: %d\n", code);
	fflush(stdout);
#endif

	if (code == start && (base == 0 || strcmp(base->id.name, name) != 0)) {
#if DEBUG_CONTAINER > 1
		printf("Container: Component not found %s; start: %d\n", name, start);
		fflush(stdout);
#endif

		base = 0;
	} else {
		if (code == 0) {
			code = size - 1;
		} else {
			code--;
		}

		components[code].isRemoved = GUI_TRUE;
		components[code].component = 0;
		used--;

#if DEBUG_CONTAINER > 1
		printf(
				"Container:Component found and removed. code: %d; start: %d; used: %d\n",
				code, start, used);
		fflush(stdout);
#endif
	}

	return (COMPONENT*) base;
}

void containerClear() {
	int i;

	if(used == 0) {
		return;
	}

	for (i = 0; i < size; i++) {
#if DEBUG_CONTAINER > 1
		printf("Container: Clear %d: removed: %d; address: %08X\n", i,
				components[i].isRemoved, (unsigned int) components[i].component);
		fflush(stdout);
#endif

		if (components[i].isRemoved == GUI_FALSE && components[i].component
				!= 0) {
#if DEBUG_CONTAINER > 1
			printf("Container: Clear %d: name: %s\n", i,
					((BASE_COMPONENT*) components[i].component)->id.name);
			fflush(stdout);
#endif
			componentRemove(components[i].component);

#if DEBUG_CONTAINER > 1
			dispContainer();
#endif
		}
	}
}

COMPONENT* containerGetComponent(char* name) {
	unsigned int code = containerCalculateHashCode(name) % size;
	unsigned int start = code;
	BASE_COMPONENT *base = 0;
	CONTAINER_ELEMENT *element = 0;

	do {
		element = &components[code++];
		base = (BASE_COMPONENT*) element->component;

		if (code == size) {
			code = 0;
		}
	} while (code != start && (element->isRemoved == GUI_TRUE || (base != 0
			&& strcmp(base->id.name, name) != 0)));

	if (code == start && (base == 0 || strcmp(base->id.name, name) != 0)) {
		base = 0;
	}

	return (COMPONENT*) base;
}

void containerInitIterator() {
	iterator = 0;

	while (iterator < size && (components[iterator].isRemoved == GUI_TRUE
			|| components[iterator].component == 0)) {
		iterator++;
	}

	if (iterator == size) {
		iterator = -1;
	}
}

int containerHasNext() {
	return (iterator == -1 ? GUI_FALSE : GUI_TRUE);
}

COMPONENT* containerGetNext() {
	COMPONENT* component = components[iterator++].component;

	while (iterator < size && (components[iterator].isRemoved == GUI_TRUE
			|| components[iterator].component == 0)) {
		iterator++;
	}

	if (iterator == size) {
		iterator = -1;
	}

	return component;
}

void containerPrivateAddComponent(CONTAINER_ELEMENT *array,
		COMPONENT *component) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;
	unsigned int code = containerCalculateHashCode(base->id.name) % size;

	while (array[code].isRemoved == GUI_FALSE && array[code].component != 0) {
		code++;

		if (code == size) {
			code = 0;
		}
	}

	array[code].isRemoved = GUI_FALSE;
	array[code].component = component;
}

void expandArray() {
	int oldSize = size;
	CONTAINER_ELEMENT *newArray;
	int i;

	if (size == 0) {
		size = 3;
	} else {
		size += size / 3;
	}

	newArray = (CONTAINER_ELEMENT*) malloc(sizeof(CONTAINER_ELEMENT) * size);
	for (i = 0; i < size; i++) {
		newArray[i].component = 0;
		newArray[i].isRemoved = GUI_FALSE;
	}

	for (i = 0; i < oldSize; i++) {
		containerPrivateAddComponent(newArray, components[i].component);
	}

	free(components);
	components = newArray;
}

unsigned int containerCalculateHashCode(char* key) {
	unsigned int code = 0;
	int i;

	for (i = 0; i < strlen(key); i++) {
		code = (code << 5) - code; // same as java api: key * 31 == (key << 5) - key
		code += (unsigned int) key[i];
	}

	return code;
}

#if DEBUG_CONTAINER > 1
void dispContainer() {
	int i;

	for (i = 0; i < size; i++) {
		printf("Element[%d]: removed: %d; address: %08X\n", i,
				components[i].isRemoved, (unsigned int) components[i].component);
	}

	fflush(stdout);
}
#endif
