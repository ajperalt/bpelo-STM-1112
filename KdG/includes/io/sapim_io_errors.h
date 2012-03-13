
#ifndef	__SAPIM_IO_ERRORS__
#define	__SAPIM_IO_ERRORS__

#include "../sapim_igep_errors.h"

/**
 * \file sapim_io_errors.h
 *
 * \brief Defines some errors for IO
 */

#define	IO_SUCCESS		SAPIM_SUCCESS
#define	IO_ERROR		SAPIM_ERROR

#define	IO_ERROR_OPEN				SAPIM_NEXT_ERROR
#define	IO_ERROR_READ				SAPIM_NEXT_ERROR-1
#define	IO_ERROR_WRITE				SAPIM_NEXT_ERROR-2
#define	IO_ERROR_LIBRARY_OPEN		SAPIM_NEXT_ERROR-3
#define	IO_ERROR_LIBRARY_FUNCTION	SAPIM_NEXT_ERROR-4

#endif
