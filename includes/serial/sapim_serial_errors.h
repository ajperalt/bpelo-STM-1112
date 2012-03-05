/*
 * sapim_serial_errors.h
 *
 *  Created on: Apr 25, 2011
 *      Author: philip
 */

#ifndef SAPIM_SERIAL_ERRORS_H_
#define SAPIM_SERIAL_ERRORS_H_


/**
 * \file sapim_serial_errors.h
 *
 * \brief Error codes used by the serial communication
 */

#include "../../includes/sapim_igep_errors.h"

#define	SERIAL_SUCCESS				SAPIM_SUCCESS
#define	SERIAL_ERROR				SAPIM_ERROR

#define	SERIAL_LOCAL_ERROR			SAPIM_NEXT_ERROR
#define	SERIAL_NOT_OPENED			SERIAL_LOCAL_ERROR-1
#define	SERIAL_PORT_ALREADY_OPENED	SERIAL_NOT_OPENED-1

#endif /* SAPIM_SERIAL_ERRORS_H_ */
