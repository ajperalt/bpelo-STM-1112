/*
 * circle.h
 *
 *  Created on: May 19, 2011
 *      Author: philip
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

/**
 * \file circle.h
 *
 * \brief Has some functions
 */

/**
 * \brief Remove space allocated specific for the circle
 *
 * \param circle The circle which must be freed
 */
void removeCircle(CIRCLE* circle);

/**
 * \brief Draw the circle
 *
 * @param circle The circle that needs to be drawn.
 * @return GUI_SUCCESS on success.
 */
int drawCircle(CIRCLE* circle);

/**
 * \brief Calculate the size of the circle
 *
 * @param circle The circle of which you want to calculate the size
 * @param width Here we will store the width
 * @param height Here we will store the height
 */
void circleCalculateSize(CIRCLE* circle, short *width, short *height);

#endif /* CIRCLE_H_ */
