
#ifndef __SAPIM_IO_FUNCTIONS__
#define	__SAPIM_IO_FUNCTIONS__

#include "sapim_io_errors.h"

/**
 * \file sapim_io_functions.h
 *
 * \brief Lists the public functions for I/O of the igep
 */

/**
 * \brief Return the text of the last error
 *
 * @return A pointer to a character array
 */
char* ioGetLastError();

/**
 * \brief Create an IO port.
 *
 * @param ioNumber The number of the port you want to use
 * @return IO_SUCCESS on success
 */
int ioCreate(int ioNumber);

/**
 * \brief Set the direction of a port
 *
 * @param ioNumber The number of the port you want to use
 * @param direction \a IO_DIRECTION_IN (in) or \a IO_DIRECTION_OUT (out)
 * @return IO_SUCCESS on success
 */
int ioSetDirection(int ioNumber, char* direction);

/**
 * \brief Set the value of a port
 *
 * @param ioNumber The number of the port you want to use
 * @param value 1 for active, 0 for not active
 * @return IO_SUCCESS on success
 */
int ioSetValue(int ioNumber, int value);

/**
 * \brief Get the value of a port
 *
 * @param ioNumber The number of the port you want to use
 * @return 1 on active, 0 on not active
 */
int ioGetValue(int ioNumber);

/**
 * \brief Set the port active_low or not
 *
 * @param ioNumber The number of the port you want to use
 * @param value IO_ACTIVE_LOW for active low, IO_ACTIVE_HIGH for active high
 * @return IO_SUCCESS on success
 */
int ioSetActiveLow(int ioNumber, int value);

#endif
