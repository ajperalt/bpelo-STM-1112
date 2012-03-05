/*
 * button.h
 *
 *  Created on: May 7, 2011
 *      Author: philip
 */

#ifndef BUTTON_H_
#define BUTTON_H_

/**
 * \file button.h
 *
 * \brief Has some functions
 */

#include "../../includes/gui/sapim_gui_all.h"

/**
 * \brief Remove space allocated specific for the button
 *
 * \param button The button which must be freed
 */
void removeButton(BUTTON* button);

/**
 * \brief Draw the button
 *
 * @param button The button that needs to be drawn.
 * @return GUI_SUCCESS on success.
 */
int drawButton(BUTTON* button);

/**
 * \brief Calculate the size of the button
 *
 * @param button The button of which you want to calculate the size
 * @param width Here we will store the width
 * @param height Here we will store the height
 */
void buttonCalculateSize(BUTTON* button, short *width, short *height);

#endif /* BUTTON_H_ */
