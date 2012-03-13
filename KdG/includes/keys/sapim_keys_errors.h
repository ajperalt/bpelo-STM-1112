
#ifndef	__SAPIM_KEYS_ERRORS__
#define	__SAPIM_KEYS_ERRORS__


/**
 * \file sapim_keys_errors.h
 *
 * \brief Lists some error values used by the keys-functions
 */

#include "../sapim_igep_errors.h"

#define	KEYS_KEYSTATE_CHANGED	1

#define	KEYS_SUCCESS		SAPIM_SUCCESS
#define	KEYS_ERROR			SAPIM_ERROR

#define KEYS_TRUE			SAPIM_TRUE
#define KEYS_FALSE			SAPIM_FALSE

#define	KEYS_STATE_CHANGED	KEYS_SUCCESS
#define	KEYS_STATE_UNCHANGED	1

#define	KEYS_ERROR_OPEN		SAPIM_NEXT_ERROR
#define KEYS_ERROR_READ		SAPIM_NEXT_ERROR-1
#define	KEYS_ERROR_WRITE	SAPIM_NEXT_ERROR-2
#define	KEYS_ERROR_LIBRARY	SAPIM_NEXT_ERROR-3
#define	KEYS_IO_ERROR		SAPIM_NEXT_ERROR-4

#endif
