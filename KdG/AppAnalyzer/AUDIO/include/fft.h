#ifndef FFT_H_INCLUDED
#define FFT_H_INCLUDED

/**
 * \file fft.h
 *
 * \brief Has some functions
 */

/**
 * \brief Calculate the Fourier Transformation
 *
 * This function computes an in-place complex-to-complex FFT.
 * \a x and \a y are the real and imaginary arrays of 2^m points.
 * source: http://local.wasp.uwa.edu.au/~pbourke/miscellaneous/dft/
 *
 * @param dir The direction of the transformation
 * 				\a dir = 1: forward transformation
 * 				\a dir = -1: reverse transformation
 * @param m The length of the array = 2^\a m
 * @param x The array which holds the real part of the imaginary value
 * @param y The array which holds the imaginary part of the imaginary value
 * @return 1 on success
 */
short FFT(short int dir, long m, float *x, float *y);
#endif
