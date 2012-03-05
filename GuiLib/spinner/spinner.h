/*
 * spinner.h
 *
 *  Created on: May 7, 2011
 *      Author: philip
 */

#ifndef SPINNER_H_
#define SPINNER_H_

#include "../../includes/gui/sapim_gui_all.h"

/**
 * \file spinner.h
 *
 * \brief Has some functions and defines
 */

/**
 * \brief Remove space allocated specific for the spinner
 *
 * \param spinner The spinner which must be freed
 */
void removeSpinner(SPINNER* spinner);

/**
 * \brief Draw the spinner
 *
 * @param spinner The spinner that needs to be drawn.
 * @return GUI_SUCCESS on success.
 */
int drawSpinner(SPINNER* spinner);


/**
 * \brief Calculate the size of the spinner
 *
 * @param spinner The spinner of which you want to calculate the size
 * @param width Here we will store the width
 * @param height Here we will store the height
 */
void spinnerCalculateSize(SPINNER* spinner, short *width, short *height);

#define SPINNER_REPAINT_NOTHING 		(0)
#define	SPINNER_REPAINT_TEXT			(1)
#define SPINNER_REPAINT_BORDER			(1<<1)
#define SPINNER_REPAINT_TIANGLE_UP		(1<<2)
#define SPINNER_REPAINT_TRIANGLE_DOWN	(1<<3)
#define SPINNER_REPAINT_BACKGROUND		((1<<4) | SPINNER_REPAINT_TEXT | SPINNER_REPAINT_TIANGLE_UP | SPINNER_REPAINT_TRIANGLE_DOWN) // always paint text andd triangles when background needs to repaint
#define SPINNER_REPAINT_ALL				0xFF

#endif /* SPINNER_H_ */
