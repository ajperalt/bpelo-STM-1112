
#ifndef	__SAPIM_ENABLE_ERRORS__
#define	__SAPIM_ENABLE_ERRORS__

#include "../sapim_igep_errors.h"

/**
 * \file sapim_enable_errors.h
 *
 * \brief Has some defines
 */

#define	ENABLE_SUCCESS			SAPIM_SUCCESS
#define	ENABLE_ERROR			SAPIM_ERROR

#define	ENABLE_ERROR_OPEN		SAPIM_NEXT_ERROR
#define ENABLE_ERROR_READ		SAPIM_NEXT_ERROR-1
#define	ENABLE_ERROR_WRITE		SAPIM_NEXT_ERROR-2
#define	ENABLE_ERROR_LIBRARY	SAPIM_NEXT_ERROR-3
#define	ENABLE_IO_ERROR			SAPIM_NEXT_ERROR-4

#endif
