/*
 * sapim_gui_rectangle_functions.h
 *
 *  Created on: May 20, 2011
 *      Author: philip
 */

#ifndef SAPIM_GUI_RECTANGLE_FUNCTIONS_H_
#define SAPIM_GUI_RECTANGLE_FUNCTIONS_H_

/**
 * \file sapim_gui_rectangle_functions.h
 *
 * \brief Lists rectangle specific functions
 */

/**
 * \brief Set the rectangle its color
 *
 * @param component The rectangle
 * @param rgb The new 24-bit color
 */
void rectangleSetColor(COMPONENT* component, int rgb);
/**
 * \brief Get the rectangle its color
 *
 * @param component The rectangle
 * @return The unsloved 24-bit color (see component.h in GuiLib for the meaning of unsolved)
 */
int rectangleGetColor(COMPONENT* component);

/**
 * \brief Set the rectangle its pen type
 *
 * @param component The rectangle
 * @param type The new pen type
 */
void rectangleSetPenType(COMPONENT* component, char type);
/**
 * \brief Get the rectangle its pen type
 *
 * @param component The rectangle
 * @return The unsolved pen type (see component.h in GuiLib for the meaning of unsolved)
 */
int rectangleGetPenType(COMPONENT* component);

/**
 * \brief Set the rectangle its width
 *
 * @param component The rectangle
 * @param width The new width
 */
void rectangleSetWidth(COMPONENT* component, short width);
/**
 * \brief Get the rectangle its width
 *
 * @param component The rectangle
 * @return The width
 */
int circleGetWidth(COMPONENT* component);

/**
 * \brief Set the rectangle its height
 *
 * @param component The rectangle
 * @param height The new height
 */
void rectangleSetHeight(COMPONENT* component, short height);
/**
 * \brief Get the rectangle its height
 *
 * @param component The rectangle
 * @return The height
 */
int circleGetHeight(COMPONENT* component);

#endif /* SAPIM_GUI_RECTANGLE_FUNCTIONS_H_ */
