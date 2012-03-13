/*
 * sapim_gui_structs.h
 *
 *  Created on: Apr 25, 2011
 *      Author: philip
 */

#ifndef SAPIM_GUI_STRUCTS_H_
#define SAPIM_GUI_STRUCTS_H_

/**
 * \file structs.h
 *
 * \brief Has some structs
 */

/**
 * \struct IDENTIFICATION
 *
 * \brief This struct identifies a component.
 */
typedef struct {
	char* name; /**< The name of the component. Should be unique in the container. The container doesn't check this, it's your own responsibility at the moment. */
    /**
     * \brief The type of the component
     *
     * Could be: GUI_CIRCLE, GUI_RECTANGLE, GUI_OVAL, GUI_ROUNDRECT, GUI_LABEL, GUI_BUTTON, GUI_SPINNER
     */
	short type;
} IDENTIFICATION;

/**
 * \struct POSITION
 *
 * \brief Defines where the component should be placed and its size
 */
typedef struct {
	short x; /**<  The x-position in pixels, always left top of the component */
	short y; /**<  The y-position in pixels, always left top of the component */
	short width; /**<  The width in pixels */
	short height; /**<  The height in pixels */
} POSITION;

/**
 * \struct BASE_COMPONENT
 *
 * \brief The base of every component
 *
 * This is the base of every component!
 * Should be the first struct in new components. Then other variables can be defined.
 */
typedef struct {
	IDENTIFICATION id; /**< The identification struct which identifies the component */
	POSITION position; /**< The position of the component */

	char visible; /**< A variable to see if the component is visible */
	char focus; /**< GUI_TRUE if the component has focus, GUI_FALSE if it hasn't */
} BASE_COMPONENT;

/**
 * \struct CIRCLE
 *
 * \brief A component that only draws a circle.
 */
typedef struct {
	BASE_COMPONENT base; /**< The base of every component */

	short radius; /**< The radius of the circle */
	int color; /**< The color of the circle */
	char pen; /**< The pensize: GUI_PEN_SOLID or GUI_PEN_WIRE */
} CIRCLE;

/**
 * \struct OVAL
 *
 * \brief A Component that only draws an ellipse
 */
typedef struct {
	BASE_COMPONENT base; /**< The base of every component */

	short radiusX; /**< The horizontal radius */
	short radiusY; /**< The vertical radius */
	int color; /**< The color of the ellipse */
	char pen; /**< The pensize: GUI_PEN_SOLID or GUI_PEN_WIRE */
} OVAL;

/**
 * \struct RECTANGLE
 *
 * \brief A component that only draws a rectangle
 *
 * No extra parameters are needed for width and height, as they are already in \a base . We just use these parameters.
 */
typedef struct {
	BASE_COMPONENT base; /**< The base of every component */

	int color; /**< The color of the rectangle */
	char pen; /**< The pensize: GUI_PEN_SOLID or GUI_PEN_WIRE */
} RECTANGLE;

/**
 * \struct ROUNDRECT
 *
 * \brief Draws a rounded rectangle.
 *
 * It isn't a rounded rectangle as in paint. This one can be used to represent a roundrect spoke.
 */
typedef struct {
	BASE_COMPONENT base; /**< The base of every component */

	short outerWidth; /**< The total width of the comoponent */
	short innerWidth; /**< The effective width of the rectangle. \a innerWidth <= \a outerWidth */
	short height; /**< The height of the rounded rectangle */

	int color; /**< The color of the rectangle */
	char pen; /**< The pensize: GUI_PEN_SOLID or GUI_PEN_WIRE */
} ROUNDRECT;

/**
 * \struct LABEL
 *
 * \brief A label component
 *
 * If the text jumps to a new line, the indent is the same as the first line.
 */
typedef struct {
	BASE_COMPONENT base; /**< The base of every component */

	char* text; /**< The text on the label */
	int textColor; /**< The color of the text */
	char font; /**< The font size */
	char transparant; /**< GUI_TRUE if the label needs to be transparant, otherwise GUI_FALSE */
	int backgroundColor; /**< The background color of the label. Ignored if the label is transparant */
	int borderColor; /**< The color of the border. Will also be drawn if the label is transparant! */
} LABEL;

/**
 * \struct BUTTON
 *
 * \brief A component which holds the data for a button
 */
typedef struct {
	BASE_COMPONENT base; /**< The base of every component */

	char* text; /**< The text on the button */
	int textColor; /**< The color of the text */
	int backgroundColor; /**< The standard background color of the button */
	int backgroundFocusColor; /**< The background color when the button has the focus */
	char font; /**< The font size of the text */
	char state; /**< The state of the button (\a GUI_BTN_UP or \a GUI_BTN_DOWN) */
} BUTTON;

/**
 * \struct SPINNER
 *
 * \brief A component which holds the data for a spinner
 */
typedef struct {
	BASE_COMPONENT base; /**< The base of every component */

	float value; /**< The value of the spinner, can only be a float */
	float min; /**< The minimum value a spinner can get */
	float max; /**< The maximum value a spinner can get */
	float step; /**< The step of the spinner. nextValue = nextValue +/- step */

	int textColor; /**< The color of the text */
	int deselectedBackground; /**< The background of the spinner when it isn't selected */
	int selectedBackground; /**< The background of the spinner when it is selected */

	int focusBorderColor; /**< The border color when it is focussed */
	int unfocusBorderColor; /**< The border color when it hasn't the focus */

	int triangleColor; /**< The standard color of the triangles */
	int triangleColorPressed; /**< The color when a triangle is pressed */

	char font; /**< The font size of the text */
	char flags; /**< extra flags of the spinner: SPINNER_FOCUS, SPINNER_SELECTED, SPINNER_UP, SPINNER_DOWN */

	char repaintFlag; /**< repaint flags to optimize the draw function. Possible values see: spinner.h in GuiLib folder */
} SPINNER;


#endif /* SAPIM_GUI_STRUCTS_H_ */
