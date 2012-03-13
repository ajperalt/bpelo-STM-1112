/*
 * sapim_gui_oval_functions.h
 *
 *  Created on: May 20, 2011
 *      Author: philip
 */

#ifndef SAPIM_GUI_OVAL_FUNCTIONS_H_
#define SAPIM_GUI_OVAL_FUNCTIONS_H_

/**
 * \file sapim_gui_oval_functions.h
 *
 * \brief Lists oval specific functions
 */

/**
 * \brief Set the oval color
 *
 * @param component The oval
 * @param rgb The 24-bit color
 */
void ovalSetColor(COMPONENT* component, int rgb);
/**
 * \brief Get the oval color
 *
 * @param component The oval
 * @return The 24-bit color (unsolved, see component.h in GuiLib)
 */
int ovalGetColor(COMPONENT* component);

/**
 * \brief Set the oval pen type
 *
 * @param component The oval
 * @param type The pen type (GUI_PEN_SOLID or GUI_PEN_WIRE)
 */
void ovalSetPenType(COMPONENT* component, char type);
/**
 * \brief Get the oval pen type
 *
 * @param component The oval
 * @return The pen type (unsolved, see component.h in GuiLib)
 */
int ovalGetPenType(COMPONENT* component);

/**
 * \brief Set the oval its horizontal radius
 *
 * @param component The oval
 * @param radius The new horizontal radius
 */
void ovalSetRadiusX(COMPONENT* component, short radius);
/**
 * \brief Get the oval its horizontal radius
 *
 * @param component The oval
 * @return The horizontal radius
 */
int ovalGetRadiusX(COMPONENT* component);

/**
 * \brief Set the oval its vertical radius
 *
 * @param component The oval
 * @param radius The new vertical radius
 */
void ovalSetRadiusY(COMPONENT* component, short radius);
/**
 * \brief Get the oval its vertical radius
 *
 * @param component The oval
 * @return The vertical radius
 */
int ovalGetRadiusY(COMPONENT* component);


#endif /* SAPIM_GUI_OVAL_FUNCTIONS_H_ */
