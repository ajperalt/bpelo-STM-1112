/*
 * analyze.c
 *
 *  Created on: May 20, 2011
 *      Author: Siegfried Mercelis
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "include/fft.h"
#include "include/filter.h"
#include "include/analyze.h"
#include "include/noisefilter.h"
#include "include/audiotools.h"

int getFrequency(float* data, int signalLength, float *noiseData,
		int noiseDuration, frequency_data* result, int noisefilter_enabled) {

	int i = 0;
	result->frequency = -1;
	result->precision = -1;

	int minZeroLength = 8192;
	int maxZeroLength = 65536;
	int minSampleLength = 4096;
	int maxSampleLength = 65536;
	int lowerFrequencyLimit = 1000;
	int upperFrequencyLimit = 2500;


	if (signalLength < minSampleLength) {
		printf("Error processing sample. Useful sample part is too short.\n");
		return -1;
	}

	//---------------------------%
	// Zero padding				 %
	//---------------------------%
	// http://www.mathworks.com/support/tech-notes/1700/1702.html

	int m = nextPow(signalLength);
	int NFFT = pow(2, m);
	// compare with minimal wanted zero-padding
	if (NFFT < minZeroLength)
		NFFT = minZeroLength;

	//---------------------------%
	// Generate frequency vector %
	// Apply zero padding		 %
	//---------------------------%
	float *x, *f;
	x = (float*) malloc(sizeof(float) * NFFT);
	f = (float*) malloc(sizeof(float) * NFFT);

	for (i = 0; i < NFFT; i++) {
		// Genereer linspace van bijhorende frequenties (Samplefrequentie verdelen in intervallen)
		f[i] = (FS / 2) * i / ((NFFT / 2 + 1));

		if (i < signalLength) //data invullen
			x[i] = data[i];
		else
			//in zero padding gebied: aanvullen met 0'en
			x[i] = 0.0;
	}
	printf("Using %d frames, padded to %d (2^%d)\n", signalLength, NFFT, m);
	fflush(stdout);

	//---------------------------%
	// Zero padding				 %
	//---------------------------%

#ifdef WRITEDEBUGOUTPUT
	printf("start fft and write prefilter.raw.\n");
	fflush(stdout);
	FILE *fp;
	fp = fopen("DEBUG/prefilter.raw", "wb");
	fwrite(data, sizeof(float), NFFT, fp);
	fclose(fp);
	fp = 0;
#endif

	//---------------------------%
	// Noise filtering			 %
	//---------------------------%
	float *filteredSignal = 0;
	int filteredSignalLength = signalLength;
	if (noisefilter_enabled == 1) {
		printf("Filtering Noise\n");
		fflush(stdout);
		int mNoise = nextPow(noiseDuration);
		int NFFT_noise = pow(2, mNoise);
		float *localNoise = (float*) malloc(sizeof(float) * NFFT_noise);

		for (i = 0; i < NFFT_noise; i++) {
			if (i < noiseDuration) //data invullen
				localNoise[i] = noiseData[i];
			else
				// zero padding
				localNoise[i] = 0.0;
		}
#ifdef WRITEDEBUGOUTPUT
		FILE *fp4 = fopen("DEBUG/nnn.raw", "wb");
		fwrite(localNoise, sizeof(float), NFFT_noise, fp4);
		fclose(fp4);
#endif

		filteredSignalLength = noisefilter(x, localNoise, NFFT, NFFT_noise, FS,
				&filteredSignal);
#ifdef WRITEDEBUGOUTPUT
		FILE *fp6 = fopen("DEBUG/postfilter.raw", "wb");
		fwrite(filteredSignal, sizeof(float), filteredSignalLength, fp6);
		fclose(fp6);
#endif
		printf("Length of filtered signal: %d = 2^%d = %d\n", filteredSignalLength, m,
				NFFT);
		fflush(stdout);
		free(localNoise);
	} else {
		//if the noisefilter is disabled,continue working with the original signal.
		filteredSignal = x;
	}

	//-------------------------------------------------%
	// Normalize the signal before EQ.                 %
	// Not doing so might result in an all-zero result %
	//-------------------------------------------------%
	normalize(filteredSignal, filteredSignalLength);

#ifdef WRITEDEBUGOUTPUT
	FILE *fp5 = fopen("DEBUG/preEQ.raw", "wb");
	fwrite(filteredSignal, sizeof(float), filteredSignalLength, fp5);
	fclose(fp5);
#endif
	//----------------------------------%
	// Apply frequency filter		    %
	//----------------------------------%
	printf("Filtering (EQ).\n");
	filter(filteredSignal, filteredSignalLength);
#ifdef WRITEDEBUGOUTPUT
	FILE *fp3 = fopen("DEBUG/postEQ.raw", "wb");
	fwrite(filteredSignal, sizeof(float), filteredSignalLength, fp3);
	fclose(fp3);
	printf("EQ complete.\n");
#endif

	//----------------------------------%
	// Calculate frequency			    %
	//----------------------------------%
	float *y = (float*) malloc(sizeof(float) * NFFT);
	for (i = 0; i < NFFT; i++) {
		y[i] = 0.0;
	}
	FFT(1, m, filteredSignal, y);

	//-------------------------------------------%
	// Determine the valid frequency range.	     %
	//-------------------------------------------%
	printf("Frequency range limited from %d to %d Hz\n", lowerFrequencyLimit,
			upperFrequencyLimit);
	int upperIndex = 0;
	int lowerIndex = 0;
	while (f[upperIndex] < upperFrequencyLimit) {
		if (f[upperIndex] <= lowerFrequencyLimit) {
			lowerIndex = upperIndex;
		}
		upperIndex++;
	}
	//-------------------------------------------%
	// Find max frequency and determine if it's  %
	// within the range.						 %
	//-------------------------------------------%
	// You could also limit the search range of mx from lower to upper index,
	// but by searching the entire spectrum, this can als cature errors
	// cause by the noisefilter.
	int freqIndex = max(filteredSignal, 0, NFFT / 2 + 1); //lowerIndex, upperIndex);//NFFT/2+1);

	if ((f[freqIndex] < lowerFrequencyLimit) || (f[freqIndex]
			> upperFrequencyLimit)) {
		if (noisefilter_enabled == 1) {
			printf(
					"Frequency out of range (%f), trying again without the noisefilter.\n",
					f[freqIndex]);
			// clear th y vector
			for (i = 0; i < NFFT; i++) {
				y[i] = 0.0;
			}
			//calculate again without the noisefilter
			filter(x, NFFT);
			FFT(1, m, x, y);
			upperIndex = 0;
			lowerIndex = 0;
			while (f[upperIndex] < upperFrequencyLimit) {
				if (f[upperIndex] <= lowerFrequencyLimit) {
					lowerIndex = upperIndex;
				}
				upperIndex++;
			}
			if ((f[freqIndex] < lowerFrequencyLimit) || (f[freqIndex]
					> upperFrequencyLimit)) {
				printf("Error: Frequency out of range (%f).\n", f[freqIndex]);
				return -1;
			}
		} else {
			printf("Error: Frequency out of range (%f).\n", f[freqIndex]);
			return -1;

		}
	}
	result->frequency = f[freqIndex];
	//precision (interval between possible frequencies of the FFT)
	result->precision = ((float) FS) / ((float) NFFT);

	printf("FreqIndex: %d\nFrequency=%f\nFFT Precision: %f\n", freqIndex,
			result->frequency, result->precision);
	free(x);
	free(y);
	free(f);

	return 0;
}
