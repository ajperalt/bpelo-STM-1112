/*
 * sapim_serial_functions.h
 *
 *  Created on: May 4, 2011
 *      Author: philip
 */

#ifndef SAPIM_SERIAL_FUNCTIONS_H_
#define SAPIM_SERIAL_FUNCTIONS_H_

/**
 * \file sapim_serial_functions.h
 *
 * \brief Lists the functions for serial communication
 */

/**
 * \brief initialize the serial port
 */
int serialInitPort();
/**
 * \brief Change the baudrate of the port
 *
 * @param baudrate The new baudrate. Should be a BAUDRATE_ constant found in sapim_serialconstants.h
 * @return SERIAL_SUCCESS on success
 *
 * @warning This function doesn't works!! Can't find the solution.
 */
int serialChangeBaudRate(int baudrate);

/**
 * \brief Write data to the port
 *
 * @param cmd The command
 * @param length The length of the command
 * @param waitForResponse SERIAL_TRUE: the program will frees until there is a respons, SERIAL_FALSE: The program will continue immediatly, however, the response will still be in the buffer!
 * @return GUI_SUCCESS on succes. If \a waitForResponse == SERIAL_TRUE, then the response must me successful (=ACK).
 */
int serialWriteData(const char* cmd, int length, char waitForResponse);
/**
 * \brief Read some data from the port
 *
 * @param buff Needs to be already allocated! The result will be written in this buffer
 * @param length The length of the buff.
 * @return SERIAL_SUCCESS on success
 */
int serialReadData(char* buff, int length);


#endif /* SAPIM_SERIAL_FUNCTIONS_H_ */
