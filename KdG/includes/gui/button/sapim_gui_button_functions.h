/*
 * sapim_gui_button_functions.h
 *
 *  Created on: May 20, 2011
 *      Author: philip
 */

#ifndef SAPIM_GUI_BUTTON_FUNCTIONS_H_
#define SAPIM_GUI_BUTTON_FUNCTIONS_H_


/**
 * \file sapim_gui_button_functions.h
 *
 * \brief Lists button specific functions
 *
 */

/**
 * \brief Set the background color of a button
 *
 * @param component The button
 * @param color The 24-bit color (or special defined color)
 */
void buttonSetBackgroundColor(COMPONENT* component, int color);
/**
 * \brief Get the background color of a button (unsolved, see component.h in GuiLib)
 *
 * @param component The button
 * @return The 24-bit color (or special defined color)
 */
int buttonGetBackgroundColor(COMPONENT* component);

/**
 * \brief Set the background focus color of a button
 *
 * @param component The button
 * @param color The 24-bit color (or special defined color)
 */
void buttonSetBackgroundFocusColor(COMPONENT* component, int color);
/**
 * \brief Get the background focus color of a button
 *
 * @param component The button
 * @return The 24-bit color (or special defined color)
 */
int buttonGetBackgroundFocusColor(COMPONENT* component);

/**
 * \brief Set the button state
 *
 * @param component The button
 * @param state \a GUI_BTN_UP or \a GUI_BTN_DOWN
 */
void buttonSetState(COMPONENT* component, char state);
/**
 * \brief Get the button state
 *
 * @return \a GUI_BTN_UP or \a GUI_BTN_DOWN
 */
char buttonGetState(COMPONENT* component);

/**
 * \brief Set if the button has focus or not
 *
 * @param component The button
 * @param state \a GUI_TRUE or \a GUI_FALSE
 */
void buttonSetFocus(COMPONENT* component, char focus);

/**
 * \brief Get the focus property of the button
 *
 * @param component The button
 * @return \a GUI_TRUE or \a GUI_FALSE
 */
char buttonGetFocus(COMPONENT* component);

#endif /* SAPIM_GUI_BUTTON_FUNCTIONS_H_ */
