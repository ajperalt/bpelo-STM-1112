/*
 * circle.h
 *
 *  Created on: May 19, 2011
 *      Author: philip
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

/**
 * \file rectangle.h
 *
 * \brief Has some functions
 */

/**
 * \brief Remove space allocated specific for the rectangle
 *
 * \param rect The rectangle which must be freed
 */
void removeRectangle(RECTANGLE* rect);

/**
 * \brief Draw the rectangle
 *
 * @param rect The rectangle that needs to be drawn.
 * @return GUI_SUCCESS on success.
 */
int drawRectangle(RECTANGLE* rect);

/**
 * \brief Calculate the size of the rectangle
 *
 * @param rect The rectangle of which you want to calculate the size
 * @param width Here we will store the width
 * @param height Here we will store the height
 */
void rectangleCalculateSize(RECTANGLE* rect, short *width, short *height);

#endif /* RECTANGLE_H_ */
