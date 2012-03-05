/*
 * noisefilter.h
 *
 *  Created on: May 20, 2011
 *      Author: kdg1
 */

#ifndef NOISEFILTER_H_
#define NOISEFILTER_H_

/**
 * \file noisefilter.h
 *
 * \brief Has some defines and functions
 */

/// \def WINDOWFILE
/// The file name where we can load the window. You shouldn't change it or you should recompile AppAnalyzer
#define WINDOWFILE "data/hamming1024.txt"
/// \def WINDOWSIZE
/// The size of the window. Again, if you change it you will need to recompile AppAnalyzer
#define WINDOWSIZE 1024
/// \def HAMMING_OVERLAP
/// The overlap of the hamming window. Again ... recompile on change
#define HAMMING_OVERLAP 0.5

/**
 * \brief Try to filter out the noise (\a noisedata) in the signal (\a signal)
 *
 * A detailled description of this function can be found in ProjectPath/AppAnalyzer/AUDIO/noisefilter.c
 *
 * @param signal The signal we want to filter. It needs to be zero padded.
 * @param noisedata An array which holds the noise data, also zero padded.
 * @param signalLength	The length of the signal in samples (needs to be a power of 2)
 * @param noiseLength The length of the noise in samples (needs to be a power of 2)
 * @param Fs The sampling frequency
 * @param output A pointer where the output will be stored. This well be allocated IN this function.
 *
 * @waring \a output will be allocated inside this function. If you pass a pointer to this function, be sure it has been freed.
 */
int noisefilter(float *signal, float* noisedata, int signalLength,
		int noiseLength, int Fs, float **output);


/**
 * \brief Applies a short time fourier transform to signal.
 *
 * For a detailed explanation of this function, look at ProjectFolder/AppAnalyzer/AUDIO/noisefilter.c
 *
 * @param signal The original signal
 * @param window The window you want to use (for example the Hamming window)
 * @param signalLength The length of the signal in samples. It should be a power of 2.
 * @param noverlap The amount of samples of every window that do not overlap. Must be smaller than WINDOWSIZE (and FFT)
 * @param windowCount The total amount of windows that will be applied, taking into account the overlap.
 * @param NFFT The amount of points in each FFT
 * @param Fs he sampling frequency.	Required to calculate the time vector.
 * @param result The real part of the result will be stored in this two-
 * 				dimesional array. It should already have been allocated with a
 * 				size of windowCount by WINDOWSIZE.
 * @param Y this is where the imaginary part of the result will be stored
 *
 * @waring The function will change \a result and \a Y
 */
void stft(float *signal, float *window, int signalLength, int noverlap,
		int windowCount, int NFFT, int Fs, float **result, float **Y/*, float *t*/);


/**
 * Just a test function, you shouldn't use it.
 */
void sinetest(float *data, int length);

#endif /* NOISEFILTER_H_ */
