/*
 * sapim_gui_component_functions.h
 *
 *  Created on: May 20, 2011
 *      Author: philip
 */

#ifndef SAPIM_GUI_COMPONENT_FUNCTIONS_H_
#define SAPIM_GUI_COMPONENT_FUNCTIONS_H_

/**
 * \file sapim_gui_component_functions.h
 *
 * \brief Lists component specific functions
 */

/**
 * \brief Remove a component and ree it's resources
 *
 * @param component The component you want to remove
 */
void componentRemove(COMPONENT* component);

/**
 * \brief Draw a component
 *
 * In fact this function will call the right draw function (like buttonDraw).
 *
 * @param component The component that needs to be drawn
 * @return GUI_SUCCESS on success
 */
int componentDraw(COMPONENT* component);
/**
 * \brief Hide a component
 *
 * @param component The component that needs to be hidden
 * @return GUI_SUCCESS on success
 */
int componentHide(COMPONENT* component);

/**
 * \brief Get the width of the component
 *
 * @param component The component
 * @return The width of \a component
 */
int componentGetWidth(COMPONENT* component);
/**
 * \brief Get the height of a component
 *
 * @param component The component
 * @return The height of \a component
 */
int componentGetHeight(COMPONENT* component);

/**
 * \brief Set the x position of the component and repaint it if it visible
 *
 * @param component The component
 * @param x The new x value
 */
void componentSetX(COMPONENT* component, short x);
/**
 * \brief Return the x-position of the component
 *
 * @param component The component
 * @return The x-position of \a component
 */
short componentGetX(COMPONENT* component);

/**
 * \brief Set the y-position of the component and repaint it if it is visible
 *
 * @param component The component
 * @param y The new y-position
 */
void componentSetY(COMPONENT* component, short y);
/**
 * \brief Get the y-position of the component
 *
 * @param component The component
 * @return The y-position of \a component
 */
short componentGetY(COMPONENT* component);

/**
 * \brief Get the most right position of the component (= x + width)
 *
 * @param component The component
 * @return The most right position (x + width)
 */
int componentGetRight(COMPONENT* component);
/**
 * \brief Get the lowest position of the component (= y + height)
 *
 * @param component The component
 * @return The lowest position (y + height)
 */
int componentGetBottom(COMPONENT* component);

/**
 * \brief Set the x and y position in one function.
 *
 * It is better to use this function when the component is visible. The component will only be painted once.
 * If you should use componentSetX and componentSetY the component gets painted twice.
 *
 * @param component The component
 * @param x The new x-position
 * @param y The new y-position
 */
void componentSetLocation(COMPONENT* component, short x, short y);

/**
 * \brief Get the name of the component
 *
 * @param component The component
 * @return A pointer to the name of the component.
 */
const char* componentGetName(COMPONENT* component);

/**
 * \brief Set the font of the component
 *
 * @param component The component
 * @param font The new font
 */
void componentSetFont(COMPONENT* component, char font);

/**
 * \brief Get the font of the component
 *
 * @param component The component
 * @return The font (unsloved)
 */
char componentGetFont(COMPONENT* component);


/**
 * \brief Set the foregroundcolor (or textcolor) of the component
 *
 * @param component The component
 * @param color The new 24-bit color
 */
void componentSetForegroundColor(COMPONENT* component, int color);

/**
 * \brief Get the foregroundcolor (or textcolor) of the component
 *
 * @param component The component
 * @return The new 24-bit color (unsloved)
 */
int componentGetForegroundColor(COMPONENT* component);

/**
 * \brief Set the text of a component
 *
 * This function can only be used if the component has text (like a label or button)
 *
 * @param component The component
 * @param text The new text of the component
 * @return GUI_SUCCESS on success
 */
int componentSetText(COMPONENT* component, const char* text);

#endif /* SAPIM_GUI_COMPONENT_FUNCTIONS_H_ */
