/*
 * container.h
 *
 *  Created on: May 7, 2011
 *      Author: philip
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "../../includes/gui/sapim_gui_functions.h"

/**
 * \file container.h
 *
 * \brief Has some functions and structs
 */

/**
 * \struct CONTAINER_ELEMENT
 *
 * \brief A struct that defines some variables so we can use a hashmap
 */
typedef struct {
	COMPONENT* component; /**< The component */
	char isRemoved; /**< 1 if the container is removed, otherwise 0 */
} CONTAINER_ELEMENT;

/**
 * \brief Add a container to the hashmap.
 *
 * @param component The component that needs to be added.
 */
void containerAddComponent(COMPONENT* component);
/**
 * \brief Remove a component from the hashmap.
 *
 * The component is identified by its name.
 *
 * @param name The name of the component
 * @return The component is returned if found, otherwise 0. We do this because the container isn't releasing the memory it uses.
 */
COMPONENT* containerRemoveComponent(char* name);

#endif /* CONTAINER_H_ */
