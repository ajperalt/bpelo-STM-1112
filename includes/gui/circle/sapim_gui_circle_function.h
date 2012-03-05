/*
 * sapim_gui_circle_function.h
 *
 *  Created on: May 20, 2011
 *      Author: philip
 */

#ifndef SAPIM_GUI_CIRCLE_FUNCTION_H_
#define SAPIM_GUI_CIRCLE_FUNCTION_H_

/**
 * \file sapim_gui_circle_function.h
 *
 * \brief Lists functions for the circle component
 */

/**
 * \brief Set the circle color
 *
 * @param component The circle
 * @param rgb The 24-bit color
 */
void circleSetColor(COMPONENT* component, int rgb);
/**
 * \brief Get the circle color
 *
 * @param component The circle
 * @return The 24-bit color (unsolved, see component.h in GuiLib)
 */
int circleGetColor(COMPONENT* component);
/**
 * \brief Set the pen type
 *
 * @param component The circle
 * @param type GUI_PEN_SOLID or GUI_PEN_WIRE
 */
void circleSetPenType(COMPONENT* component, char type);
/**
 * \brief Get the circle color
 *
 * @param component The circle
 * @return GUI_PEN_SOLID or GUI_PEN_WIRE
 */
int circleGetPenType(COMPONENT* component);
/**
 * \brief Set the radius
 *
 * @param component The circle
 * @param radius The radius of the circle
 */
void circleSetRadius(COMPONENT* component, short radius);
/**
 * \brief Get the radius
 *
 * @param component The circle
 * @return The radius of the circle
 */
int circleGetRadius(COMPONENT* component);

#endif /* SAPIM_GUI_CIRCLE_FUNCTION_H_ */
