/*
 * oval.h
 *
 *  Created on: May 19, 2011
 *      Author: philip
 */

#ifndef ROUNDRECT_H_
#define ROUNDRECT_H_

/**
 * \file roundrect.h
 *
 * \brief Has some functions
 */

/**
 * \brief Remove space allocated specific for the roundrect
 *
 * \param roundrect The roundrect which must be freed
 */
void removeRoundrect(ROUNDRECT* roundrect);

/**
 * \brief Draw the roundrect
 *
 * @param roundrect The roundrect that needs to be drawn.
 * @return GUI_SUCCESS on success.
 */
int drawRoundrect(ROUNDRECT* roundrect);

/**
 * \brief Calculate the size of the roundrect
 *
 * @param roundrect The roundrect of which you want to calculate the size
 * @param width Here we will store the width
 * @param height Here we will store the height
 */
void roundrectCalculateSize(ROUNDRECT* roundrect, short *width, short *height);

#endif /* ROUNDRECT_H_ */
