/*
 * sapim_gui_errors.h
 *
 *  Created on: Apr 25, 2011
 *      Author: philip
 */

#ifndef SAPIM_GUI_ERRORS_H_
#define SAPIM_GUI_ERRORS_H_

#include "../sapim_igep_errors.h"

/**
 * \file sapim_gui_errors.h
 *
 * \brief Some GUI error codes
 */

#define	GUI_SUCCESS					SAPIM_SUCCESS
#define	GUI_ERROR					SAPIM_ERROR

#define GUI_ERROR_RESTORE_SETTINGS	SAPIM_NEXT_ERROR
#define GUI_ERROR_NO_TEXT			GUI_ERROR_RESTORE_SETTINGS-1
#define GUI_ERROR_NO_BACKGROUND		GUI_ERROR_NO_TEXT-1

#endif /* SAPIM_GUI_ERRORS_H_ */
