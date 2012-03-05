/*
 * sapim_gui_functions.h
 *
 *  Created on: May 4, 2011
 *      Author: philip
 */

#ifndef SAPIM_GUI_FUNCTIONS_H_
#define SAPIM_GUI_FUNCTIONS_H_

/**
 * \file sapim_gui_functions.h
 *
 * \brief Lists guie functions
 */

/**
 * \typedef COMPONENT
 *
 * The user will use a void pointer to a component. The user doesn't need to know more
 * and the user can't change the structs directly.
 */
typedef void* COMPONENT;

#include "component/sapim_gui_component_functions.h"
#include "label/sapim_gui_label_functions.h"
#include "button/sapim_gui_button_functions.h"
#include "spinner/sapim_gui_spinner_functions.h"
#include "circle/sapim_gui_circle_function.h"
#include "oval/sapim_gui_oval_functions.h"
#include "roundrect/sapim_gui_roundrect_functions.h"
#include "rectangle/sapim_gui_rectangle_functions.h"


/**
 * \brief Initiliaze the GUI with standard values.
 *
 * See sapim_gui_constants for the standard values.
 *
 * @return GUI_SUCCESS on success
 */
int guiInit(void);


/**
 * \brief Create a new label
 *
 * @param name The name of the label. The label copies the name to its's own buffer. (should be unique)
 * @param text The text on the label. The label copies the text to it's own buffer.
 * @param x The x-position of the label in pixels
 * @param y The y-position of the label in pixels
 * @return 0 if the component isn't created
 */
COMPONENT* createLabel(const char* name, const char* text, short x, short y);
/**
 * \brief Create a new button
 *
 * @param name The name of the button. The button copies the name to its's own buffer. (should be unique)
 * @param text The text on the button. The button copies the text to it's own buffer.
 * @param x The x-position of the label in pixels
 * @param y The y-position of the label in pixels
 * @return 0 if the component isn't created
 */
COMPONENT* createButton(const char* name, const char* text, short x, short y);
/**
 * \brief Create a new spinner
 *
 * @param name The name of the spinner. The spinner copies the name to its's own buffer. (should be unique)
 * @param value The starting value on the spinner
 * @param min The minimum value of the spinner
 * @param max The maximum value of the spinner
 * @param step The step of the spinner
 * @param x The x-position of the spinner in pixels
 * @param y The y-position of the spinner in pixels
 * @return 0 if the component isn't created
 */
COMPONENT* createSpinner(const char* name, float value, float min, float max,
		float step, short x, short y);
/**
 * \brief Create a new circle
 *
 * @param name The name of the circle. The circle copies the name to its's own buffer. (should be unique)
 * @param x The x-position of the circle in pixels (left top of the circle)
 * @param y The y-position of the circle in pixels (left top of the circle)
 * @param radius The radius of the circle
 * @param rgb The 24-bit color of the circle
 * @param pen The pen type of the circle (GUI_PEN_SOLID or GUI_PEN_WIRE)
 * @return 0 if the component isn't created
 */
COMPONENT* createCircle(const char* name, short x, short y, short radius,
		int rgb, char pen);
/**
 * \brief Create a new rectangle
 *
 * @param name The name of the rectangle. The rectangle copies the name to its's own buffer. (should be unique)
 * @param x The x-position of the rectangle in pixels (left top of the rectangle)
 * @param y The y-position of the rectangle in pixels (left top of the rectangle)
 * @param width The width of the rectangle
 * @param height The height of the rectangle
 * @param rgb The 24-bit color of the rectangle
 * @param pen The pen type of the rectangle (GUI_PEN_SOLID or GUI_PEN_WIRE)
 * @return 0 if the component isn't created
 */
COMPONENT* createRectangle(const char* name, short x, short y, short width,
		short height, int color, char pen);
/**
 * \brief Create a new oval
 *
 * @param name The name of the oval. The oval copies the name to its's own buffer. (should be unique)
 * @param x The x-position of the oval in pixels (left top of the oval)
 * @param y The y-position of the oval in pixels (left top of the oval)
 * @param radiusX The horizontal radius of the oval
 * @param radiusY The vertical radius of the oval
 * @param rgb The 24-bit color of the oval
 * @param pen The pen type of the oval (GUI_PEN_SOLID or GUI_PEN_WIRE)
 * @return 0 if the component isn't created
 */
COMPONENT* createOval(const char* name, short x, short y, short radiusX,
		short radiusY, int color, char pen);
/**
 * \brief Create a new oval
 *
 * @param name The name of the roundrect. The roundrect copies the name to its's own buffer. (should be unique)
 * @param x The x-position of the roundrect in pixels (left top of the roundrect)
 * @param y The y-position of the roundrect in pixels (left top of the roundrect)
 * @param outerWidth The outer width of the roundrect
 * @param innerWidth The inner width of the roundrect (\a innerWidth <= \a outerWidth)
 * @param height The height of the roundrect
 * @param rgb The 24-bit color of the roundrect
 * @param pen The pen type of the roundrect (GUI_PEN_SOLID or GUI_PEN_WIRE)
 * @return 0 if the component isn't created
 */
COMPONENT* createRoundrect(const char* name, short x, short y, short outerWidth,
		short innerWidth, short height, int color, char pen);


/**
 * \brief Clear the whole screen
 *
 * @return GUI_SUCCESS on success
 */
int clearScreen(void);
/**
 * \brief Clear a part of the screen
 *
 * @param x The x-position of the most left top position
 * @param y The y-position of the most left top position
 * @param width The width of the part you want to clear
 * @param height The height of the part you want to clear
 * @return GUI_SUCCESS on success
 */
int clearPart(int x, int y, int width, int height);

/**
 * \brief Set the background of the screen
 */
int setBackgroundColor(int rgb);
/**
 * \brief Replace the background to a new color
 *
 * The old background color will be replaced by the new one on the screen
 */
int replaceBackgroundColor(int rgb);
/**
 * \brief Return the background color
 */
int getBackgroundColor();
/**
 * \brief Set a new pen type
 *
 * @param type GUI_PEN_SOLID or GUI_PEN_WIRE
 */
int setPenType(char type);
/**
 * \brief Get the pen type
 */
char getPenType();
/**
 * \brief Set a new default font
 *
 * @param size GUI_FONT_SMALL, GUI_FONT_MEDIUM, GUI_FONT_LARGE, GUI_FONT_LARGEST
 */
int setDefaultFont(char size);
/**
 * \brief Return the default font
 */
char getDefaultFont();
/**
 * \brief Set new drawn texts to transparant
 */
int setTransparant();
/**
 * \brief return if new drawn texts are transparant or not
 *
 * @return GUI_TRUE or GUI_FALSE
 */
int getTransparant();
/**
 * \brief Set new drawn texts to opaque
 */
int setOpaque();
/**
 * \brief return if new drawn texts are opaque or not
 *
 * @return GUI_TRUE or GUI_FALSE
 */
int getOpaque();
/**
 * \brief Set a new standard foregroundcolor
 */
int setForegroundColor(int rgb);
/**
 * \brief Get the standard foregroundcolor
 */
int getForegroundColor();


/*
 * Some functions to get/set default button properties.
 * Newly created buttons will get those default values
 */
int setDefaultButtonBackgroundColor(int color);
int getDefaultButtonBackgroundColor();

int setDefaultButtonForegroundColor(int color);
int getDefaultButtonForegroundColor();

int setDefaultButtonBackgroundFocusColor(int color);
int getDefaultButtonBackgroundFocusColor();


/*
 * Some functions to get/set default spinner properties.
 * Newly created spinner will get those default values
 */
int setDefaultSpinnerBackgroundColor(int color);
int getDefaultSpinnerBackgroundColor();

int setDefaultSpinnerBackgroundSelectedColor(int color);
int getDefaultSpinnerBackgroundSelectedColor();

int setDefaultspinnerForegroundColor(int color);
int getDefaultSpinnerForegroundColor();

int setDefaultSpinnerBorderColor(int color);
int getDefaultSpinnerBorderColor();

int setDefaultSpinnerBorderFocusColor(int color);
int getDefaultSpinnerBorderFocusColor();

int setDefaultSpinnerTriangleColor(int color);
int getDefaultSpinnerTriangleColor();

int setDefaultSpinnerTrianglePressedColor(int color);
int getDefaultSpinnerTrianglePressedColor();

/**
 * \brief Clear the container
 *
 * The components are alose getting freed and removed from the screen.
 */
void containerClear();
/**
 * \brief Get a component with a specific name
 */
COMPONENT* containerGetComponent(char* name);
/**
 * \brief Initialize an iterator
 */
void containerInitIterator();
/**
 * \brief Check if the container has a next component
 *
 * @return GUI_TRUE/GUI_FALSE
 */
int containerHasNext();
/**
 * \brief Return the next component found by the iterator
 */
COMPONENT* containerGetNext();


/**
 * \brief Get the width of the display
 */
int getDisplayWidth();
/**
 * \brief Get the height of the display
 */
int getDisplayHeight();

#endif /* SAPIM_GUI_FUNCTIONS_H_ */
