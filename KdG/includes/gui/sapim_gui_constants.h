/*
 * sapim_gui_constants.h
 *
 *  Created on: May 5, 2011
 *      Author: philip
 */
 
/**
 * \file sapim_gui_constants.h
 *
 * \brief Lists GUI defines
 */

#ifndef SAPIM_GUI_CONSTANTS_H_
#define SAPIM_GUI_CONSTANTS_H_

#define	GUI_TRUE			1
#define	GUI_FALSE			0

#define GUI_PEN_SOLID		0x00
#define GUI_PEN_WIRE		0x01

#define GUI_FONT_SMALL		0x00
#define GUI_FONT_MEDIUM		0x01
#define GUI_FONT_LARGE		0x02
#define GUI_FONT_LARGEST	0x03

#define GUI_BTN_DOWN		0x00
#define GUI_BTN_UP			0x01

#define	GUI_USE_DEFAULT_FOREGROUND_COLOR	0x01000000/**< This color get translated on the fly to the default foreground color */
#define	GUI_USE_DEFAULT_BACKGROUND_COLOR	0x02000000 /**< This color get translated on the fly to the default background color */
#define	GUI_USE_DEFAULT_FONT				0x10 /**< This font get translated on the fly to the default font */

/*
 * standard settings of the screen
 */
#define	GUI_FONT						GUI_FONT_LARGE
#define	GUI_BACKGROUND					0x00FFFFFF
#define	GUI_FOREGROUND					0x00000000
#define	GUI_PEN							GUI_PEN_SOLID

#define	GUI_BUTTON_BACKGROUND			0x00B8B8B8
#define	GUI_BUTTON_BACKGROUND_FOCUS		0x00888888
#define	GUI_BUTTON_FOREGROUND			0x01000000

#define	GUI_SPINNER_BACKGROUND			0x00C8C8C8
#define	GUI_SPINNER_BACKGROUND_SELECTED	0x00888888
#define	GUI_SPINNER_BORDER				0x00FFFFFF
#define GUI_SPINNER_BORDER_FOCUS		0x00FF0000
#define	GUI_SPINNER_TRIANGLE			0x000000FF
#define	GUI_SPINNER_TRIANGLE_PRESSED	0x00FF0000
#define	GUI_SPINNER_FOREGROUND			0x01000000

/*
 * component flags
 */
#define	COMPONENT_FOCUS					0x01
#define	COMPONENT_SELECTED				0x02

/*
 * spinner flags
 */
#define	SPINNER_FOCUS					COMPONENT_FOCUS
#define	SPINNER_SELECTED				COMPONENT_SELECTED
#define	SPINNER_UP						(COMPONENT_SELECTED<<1)
#define	SPINNER_DOWN					(SPINNER_UP<<1)

/*
 * label constants
 */
#define	MAX_LABEL_LENGTH				255

#endif /* SAPIM_GUI_CONSTANTS_H_ */
