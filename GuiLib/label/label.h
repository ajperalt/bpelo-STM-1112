/*
 * label.h
 *
 *  Created on: May 7, 2011
 *      Author: philip
 */

#ifndef LABEL_H_
#define LABEL_H_

#include "../../includes/gui/sapim_gui_all.h"

/**
 * \file label.h
 *
 * \brief Has some functions
 */

/**
 * \brief Remove space allocated specific for the label
 *
 * \param label The label which must be freed
 */
void removeLabel(LABEL* label);

/**
 * \brief Draw the label
 *
 * @param label The label that needs to be drawn.
 * @return GUI_SUCCESS on success.
 */
int drawLabel(LABEL* label);

/**
 * \brief Calculate the size of the label
 *
 * @param label The label of which you want to calculate the size
 * @param width Here we will store the width
 * @param height Here we will store the height
 */
void labelCalculateSize(LABEL* label, short *width, short *height);

#endif /* LABEL_H_ */
