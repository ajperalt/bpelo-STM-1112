
#ifndef __SAPIM_KEYS_FUNCTIONS__
#define	__SAPIM_KEYS_FUNCTIONS__


/**
 * \file sapim_keys_functions.h
 *
 * \brief Lists the keys-functions
 */

#include "sapim_keys_errors.h"

/**
 * \brief return the last error-text set by a keys-function
 */
char* keysGetLastError();

/**
 * \brief initialize all keys
 */
int keysInit();
/**
 * \brief Get a pointer to all keys
 *
 * @param length If length != 0 then the function will store the size of the array in length
 */
int* keysGetAll(int *length);
/**
 * \brief Get the value of the right key
 *
 * @return KEYS_TRUE = down, KEYS_FALSE = up
 */
int keysGetRight();
/**
 * \brief Get the value of the left key
 *
 * @return KEYS_TRUE = down, KEYS_FALSE = up
 */
int keysGetLeft();
/**
 * \brief Get the value of the up key
 *
 * @return KEYS_TRUE = down, KEYS_FALSE = up
 */
int keysGetUp();
/**
 * \brief Get the value of the down key
 *
 * @return KEYS_TRUE = down, KEYS_FALSE = up
 */
int keysGetDown();
/**
 * \brief Get the value of the enter key
 *
 * @return KEYS_TRUE = down, KEYS_FALSE = up
 */
int keysGetEnter();
/**
 * \brief This functions frees the application until the user has pressed on a key
 */
int keysWaitOnPress();
/**
 * \brief Refreshes the key valuess
 *
 * @return ret < 0: error
 * 			ret == 0: at least one key its state was changed
 * 			ret > 1: no keys were changed
 */
int keysRefresh();
/**
 * \brief Sets all values of the keys to 0
 */
void keysClear();

#endif
