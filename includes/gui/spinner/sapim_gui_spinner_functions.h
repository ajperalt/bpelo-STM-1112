/*
 * sapim_gui_spinner_functions.h
 *
 *  Created on: May 20, 2011
 *      Author: philip
 */

#ifndef SAPIM_GUI_SPINNER_FUNCTIONS_H_
#define SAPIM_GUI_SPINNER_FUNCTIONS_H_

/**
 * \file sapim_gui_spinner_functions.h
 *
 * \brief The functions specific for a spinner
 *
 * Here are some setters and getters for a spinner. I think the functions tell enough.
 */

/**
 * \brief The spinner goes in sellection mode
 *
 * When the spinner is in selection mode, it takes over the control of the application.
 * The spinner reads the key values from the GPIO. When the up/down key is pressed, the value in the
 * spinner gets incremented/decremented with a value of step.
 *
 * When the key up/down is holded down, the spinner will scroll up/down. If an internal counter reach
 * the value of 10, the step will be multiplied with 5, so the spinner goes faster.
 * When the keys are released, the normal step is restored.
 *
 * The user can exit the spinner by pressing the "enter"-key.
 *
 * @param component The spinner
 */
void spinnerEnterSelectionMode(COMPONENT* component);

void spinnerSetFocus(COMPONENT* component, char focus);
void spinnerSetSelected(COMPONENT* component, char selected);
void spinnerSetUpSelected(COMPONENT* component, char selected);
void spinnerSetDownSelected(COMPONENT* component, char selected);
void spinnerSetValue(COMPONENT* component, float value);
void spinnerSetMin(COMPONENT* component, float min);
void spinnerSetMax(COMPONENT* component, float max);
void spinnerSetStep(COMPONENT* component, float step);
void spinnerIncValue(COMPONENT* component);
void spinnerDecValue(COMPONENT* component);

void spinnerSetForegroundColor(COMPONENT* component, int color);
void spinnerSetDeselectedBackground(COMPONENT* component, int color);
void spinnerSetSelectedBackground(COMPONENT* component, int color);
void spinnerSetFocusBorderColor(COMPONENT* component, int color);
void spinnerSetUnfocusBorderColor(COMPONENT* component, int color);
void spinnerSetTriangleColor(COMPONENT* component, int color);
void spinnerSetTriangleColorPressed(COMPONENT* component, int color);

// getters
int spinnerGetFocus(COMPONENT* component);
int spinnerGetSelected(COMPONENT* component);
int spinnerGetUpSelected(COMPONENT* component);
int spinnerGetDownSelected(COMPONENT* component);
float spinnerGetValue(COMPONENT* component);
float spinnerGetMin(COMPONENT* component);
float spinnerGetMax(COMPONENT* component);
float spinnerGetStep(COMPONENT* component);

int spinnerGetForegroundColor(COMPONENT* component);
int spinnerGetDeselectedBackground(COMPONENT* component);
int spinnerGetSelectedBackground(COMPONENT* component);
int spinnerGetFocusBorderColor(COMPONENT* component);
int spinnerGetUnfocusBorderColor(COMPONENT* component);
int spinnerGetTriangleColor(COMPONENT* component);
int spinnerGetTriangleColorPressed(COMPONENT* component);



#endif /* SAPIM_GUI_SPINNER_FUNCTIONS_H_ */
