/*
 * filter.h
 *
 *  Created on: May 20, 2011
 *      Author: kdg1
 */

#ifndef FILTER_H_
#define FILTER_H_

/**
 * \file filter.h
 *
 * \brief Has some functions
 */

/**
 * \brief Filter out some frequencies we don't need
 *
 * @param data The data on which we will use the equalizer
 * @param length The length of the data
 *
 * @waring The function will change \a data
 */
void filter(float *data, int length);

#endif /* FILTER_H_ */
