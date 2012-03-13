/*
 * sapim_gui_roundrect_functions.h
 *
 *  Created on: May 20, 2011
 *      Author: philip
 */

#ifndef SAPIM_GUI_ROUNDRECT_FUNCTIONS_H_
#define SAPIM_GUI_ROUNDRECT_FUNCTIONS_H_

/**
 * \file sapim_gui_roundrect_functions.h
 *
 * \brief Lists roundrect specific functions
 */

/**
 * \brief Set the roundrect its color
 *
 * @param component The roundrect
 * @param rgb The new 24-bit color
 */
void roundrectSetColor(COMPONENT* component, int rgb);
/**
 * \brief Get the roundrect its color
 *
 * @param component The roundrect
 * @return The unsolved 24-bit color (seen component.h in GuiLib for the meaning of unsolved)
 */
int roundrectGetColor(COMPONENT* component);

/**
 * \brief Set the roundrect its pen type
 *
 * @param component The roundrect
 * @param type The new pen type
 */
void roundrectSetPenType(COMPONENT* component, char type);
/**
 * \brief Get the roundrect its pen type
 *
 * @param component The roundrect
 * @return The unsolved pen type (seen component.h in GuiLib for the meaning of unsolved)
 */
int roundrectGetPenType(COMPONENT* component);

/**
 * \brief Set the roundrect its outer width
 *
 * @param component The roundrect
 * @param width the new outer width
 */
void roundrectSetOuterWidth(COMPONENT* component, short width);
/**
 * \brief Get the roundrect its outer width
 *
 * @param component The roundrect
 * @return The outer width of the roundrect
 */
int roundrectGetOuterWidth(COMPONENT* component);

/**
 * \brief Set the roundrect its inner width
 *
 * @param component The roundrect
 * @param width the new inner width
 */
void roundrectSetInnerWidth(COMPONENT* component, short width);
/**
 * \brief Get the roundrect its inner width
 *
 * @param component The roundrect
 * @return The inner width of the roundrect
 */
int roundrectGetInnerWidth(COMPONENT* component);

/**
 * \brief Set the roundrect its height
 *
 * @param component The roundrect
 * @param height the new height
 */
void roundrectSetHeight(COMPONENT* component, short height);
/**
 * \brief Get the roundrect its height
 *
 * @param component The roundrect
 * @return The height of the roundrect
 */
int roundrectGetHeight(COMPONENT* component);


#endif /* SAPIM_GUI_ROUNDRECT_FUNCTIONS_H_ */
