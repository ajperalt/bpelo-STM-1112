/*
 * oval.h
 *
 *  Created on: May 19, 2011
 *      Author: philip
 */

#ifndef OVAL_H_
#define OVAL_H_


/**
 * \file oval.h
 *
 * \brief Has some functions
 */

/**
 * \brief Remove space allocated specific for the oval
 *
 * \param oval The oval which must be freed
 */
void removeOval(OVAL* oval);

/**
 * \brief Draw the oval
 *
 * @param oval The oval that needs to be drawn.
 * @return GUI_SUCCESS on success.
 */
int drawOval(OVAL* oval);

/**
 * \brief Calculate the size of the oval
 *
 * @param oval The oval of which you want to calculate the size
 * @param width Here we will store the width
 * @param height Here we will store the height
 */
void ovalCalculateSize(OVAL* oval, short *width, short *height);

#endif /* OVAL_H_ */
