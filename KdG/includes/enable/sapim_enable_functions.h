
#ifndef __SAPIM_ENABLE_FUNCTIONS__
#define	__SAPIM_ENABLE_FUNCTIONS__

#include "sapim_enable_errors.h"

/**
 * \file sapim_enable_functions.h
 *
 * \brief Has some functions
 */

/**
 * \brief Get the last error set by enableLib
 *
 * @return A pointer to the error-string
 */
char* enableGetLastError();

/**
 * \brief Initialize a port so you can use it to enable/disable it.
 *
 * @param number The port number. Could be:
 *                  GPIO_MIC
 *                  GPIO_SOLENOID
 *                  GPIO_LCD_RESET
 * @param direction "in" or "out"
 * @param active_low 1 is active low, 0 is active high
 * @param active Set the beginning value to active or not active
 * @return ENABLE_SUCCESS on success
 */
int enableInit(int number, char* direction, int active_low, int active);
/**
 * \brief Enable the I/O-port
 *
 * @param ioNumber The port number. Could be:
 *                  GPIO_MIC
 *                  GPIO_SOLENOID
 *                  GPIO_LCD_RESET
 * @return ENABLE_SUCCESS on success
 */
int enable(int ioNumber);
/**
 * \brief Disable the I/O-port
 *
 * @param ioNumber The port number. Could be:
 *                  GPIO_MIC
 *                  GPIO_SOLENOID
 *                  GPIO_LCD_RESET
 * @return ENABLE_SUCCESS on success
 */
int disable(int ioNumber);

#endif
