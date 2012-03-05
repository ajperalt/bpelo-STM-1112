/*
 * sapim_gui_label_functions.h
 *
 *  Created on: May 20, 2011
 *      Author: philip
 */

#ifndef SAPIM_GUI_LABEL_FUNCTIONS_H_
#define SAPIM_GUI_LABEL_FUNCTIONS_H_

/**
 * \file sapim_gui_label_functions.h
 *
 * \brief Lists label specific functions
 */

/**
 * \brief Moves splitted words to a new line
 *
 * @param component The label
 */
void labelWordWrap(COMPONENT* component);


/**
 * \brief Set the background color of the label
 *
 * @param component The label
 * @param rgb The 24-bit color
 */
void labelSetBackgroundColor(COMPONENT* component, int rgb);

/**
 * \brief Get the background color of the label
 *
 * @param component The label
 * @return The background color (unsolved, see component.h in GuiLib)
 */
int labelGetBackgroundColor(COMPONENT* component);

/**
 * \brief Sets the border color of the label
 *
 * @param component The label
 * @param rgb The 24-bit color
 */
void labelSetBorderColor(COMPONENT* component, int rgb);

/**
 * \brief Get the border color
 *
 * @param component The label
 * @return The border color (unsolved, see component.h in GuiLib)
 */
int labelGetBorderColor(COMPONENT* component);


#endif /* SAPIM_GUI_LABEL_FUNCTIONS_H_ */
