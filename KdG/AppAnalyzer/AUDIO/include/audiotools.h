/*
 * audiotools.h
 *
 *  Created on: May 20, 2011
 *      Author: kdg1
 */

#ifndef AUDIOTOOLS_H_
#define AUDIOTOOLS_H_

/**
 * \file audiotools.h
 *
 * \brief Has some functions
 */

/**
 * \brief Calculate the power of 2 which apply to: result >= N.
 *
 * @param N Calculates a power of 2 >= N
 * @return The calculated power
 */
int nextPow(int N);

/**
 * \brief Normalize a wave signal
 *
 * @param data The data of the wave signal
 * @param length The length of the data in samples
 *
 * @waring The function will change \a data
 */
void normalize(float *data, int length);

/**
 * \brief Searches the maximum value and returns its index
 *
 * \param data The data in which it looks
 * @param start Where the function needs to begin
 * @param end Where the function needs to stop
 * @return The index where the max could be found in data
 */
int max(float* data, int start, int end);

#endif /* AUDIOTOOLS_H_ */
