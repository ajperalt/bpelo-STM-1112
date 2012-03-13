/*
 * noisefilter.c
 *
 *  Created on: May 20, 2011
 *      Author: Siegfried Mercelis
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "include/fft.h"
#include "include/analyze.h"
#include "include/noisefilter.h"
#include "include/audiotools.h"

//----------------------------STFT(....)----------------------------//
// Applies a short time fourier transform to signal. The original   //
// signal is divided into 'windowCount' pieces with a size of 'NNFT'//
// The algorithm is an adaptation of the spectrogram function in    //
// Matlab, removing all the graphical calls and support for         //
// different types of data.											//
// Pre-conditions: zero padding should already have been applied    //
// before calling this function, the amount of windows should       //
// already be calculated as well, taking into account the overlap.  //
// The total length of te signal should be a power of 2, NFFT should//
// be as well. Window should have a size of NFFT (which equals to   //
// WINDOWSIZE. It might work with different parameters, but this    //
// hasn't been tested. 'result', 'Y' and 't' should be preallocated.//												//
// Parameters:                                                      //
// -signal: the original signal, in time domain						//
// -window: in this case we used a hamming window, it is highly     //
//  recommended to use Hamming windows with an overlap of 50%, as   //
//  this allows perfect reconstruction of the original signal when  //
//  applying the inverse FFT with the overlap-add technique			//
// -signalLength: the length of 'signal'. Should be a power of 2.	//
// -noverlap: the amount of samples of every window that do not 	//
//  overlap. Must be smaller than WINDOWSIZE (and FFT)				//
// -windowCount: the total amount of windows that will be applied,  //
//  taking into account the overlap.								//
// -NFFT: The amount of points in each FFT, in this project it equals//
//  the window size for improved performance.						//
// -Fs: The sampling frequency.	Required to calculate the time 		//
//  vector.															//
// -result: The real part of the result will be stored in this two- //
//  dimesional array. It should already have been allocated with a  //
//  size of windowCount by WINDOWSIZE. It contains 'windowCount' FFT//
//  results with a length of WINDOWSIZE.							//
// -Y: this is where the imaginary part of the result will be stored//
//  it should also be preallocated with the same size as 'result'.  //
// -t: this array will contain the time-vector of the result,       //
//  indicating the start of every window in time-domain. It should  //
//  be preallocated with a size of 'windowCount'. T has been removed//
//  in the final version, because we didn't need the vector for this//
//  application. I left in the code, however, because it might be of//
//  use in future projects.											//
// Post-condition: result, Y and t are modified.               		//
//------------------------------------------------------------------//

//#define DEBUGSTFT

void stft(float *signal, float *window, int signalLength, int noverlap,
		int windowCount, int NFFT, int Fs, float **result, float **Y/*, float *t*/) {
	printf("--------------------------------------\n");
	printf("STFT INPUT DATA:\n");
	printf("NFFT: %d\n", NFFT);
	printf("Fs: %d\n", Fs);
	printf("noverlap %d:\n", noverlap);
	printf("windowCount %d:\n", windowCount);
	printf("signallength %d:\n", signalLength);
	printf("--------------------------------------\n");

	int *colindex = (int*) malloc(sizeof(int) * windowCount);
	int i = 0;
	int j = 0;

	for (i = 0; i < windowCount; i++) {
		colindex[i] = i * (NFFT - noverlap);
#ifdef DEBUGSTFT
		printf("Col %d: %d\n", i, colindex[i]);
#endif
	}
#ifdef DEBUGSTFT
	printf("Placing x & y in columns with the proper offset.\n");
	printf("----------Working with following data: (first 3 values)------------\n");
#endif
	for (i = 0; i < windowCount; i++) {
#ifdef DEBUGSTFT
		printf("X-column %d at %d ",i, colindex[i]);
#endif
		fflush(stdout);
		for (j = 0; j < WINDOWSIZE; j++) {
#ifdef DEBUGSTFT
			printf("at %d+%d=%d\n",j, colindex[i], j%NFFT + colindex[i]);
#endif
			fflush(stdout);
			Y[i][j] = 2.22E-16;
			result[i][j] = signal[colindex[i] + j];
			// Apply the window to the array of offset signal segments.
			result[i][j] = result[i][j] * window[j];
		}
#ifdef DEBUGSTFT
		printf("%e %e %e\n", result[i][0], result[i][1], result[i][2]);
#endif
	}

	// Compute the raw STFT
	int m = nextPow(NFFT);
	printf("Calculating FFT with parameters:\n m: %d\n", m);

	for (i = 0; i < windowCount; i++) {
#ifdef DEBUGSTFT
		printf("FFT %d size %d = 2^%d\n",i, NFFT, m);
		fflush(stdout);
#endif
		FFT(1, m, result[i], Y[i]);
#ifdef DEBUGSTFT
		printf("FFT %d: %e %e %e\n", i, result[i][0], result[i][1], result[i][2]);
#endif
		fflush(stdout);
	}
	// Return a T vector whose elements are centered in the segment.
	//	for (i = 0; i < windowCount; i++) {
	//		t[i] = (float) ((colindex[i] + ((float) NFFT / 2.0))) / Fs;
	//		//Time check --> ok!
	//	}
	printf("STFT complete!\n");
	// clean up the allocated arrays
	free(colindex);
}

//----------------allocate2Dfloat(nrows,ncolumns)-------------------//
// Allocates a nrows by ncolumns array. The return value is a       //
// pointer to the allocated memory.									//
//------------------------------------------------------------------//

float ** allocate2Dfloat(int nrows, int ncolumns) {
	int i;
	float **array = (float **) malloc(nrows * sizeof(float *));
	for (i = 0; i < nrows; i++)
		array[i] = (float *) malloc(ncolumns * sizeof(float));
	return array;
}
//-------------------free2Dfloat(array,nrows)-----------------------//
// Frees a 2D-array with a height of nrows. The length of the rows  //
// doesn't matter. Can be used to clear data assigned with          //
// allocate2Dfloat. 												//
// Precondition: an array of 'nrows' by ... 						//
// Postcondition: the array is freed and the pointer is set to 0	//
// Parameters:														//
// -array: the 2D-array to be freed									//
// -nrows: the length of the first dimension of the array			//
//  The array should be of size: array[nrows][m]. The second        //
//  dimension 'm' is not required to free the memory.               //
//------------------------------------------------------------------//
void free2Dfloat(float **array, int nrows) {
	int i;
	for (i = 0; i < nrows; i++) {
		free(array[i]);
	}
	free(array);
	array = 0;

}

//-noisefilter(signal,noisedata,signalLength,noiseLength,Fs,output)-//
//																	//
// This algorithm filters out the noise of signal (time-domain),    //
// based on the spectrum calculated from noisedata.					//
// Preconditions: signal should be a dataset of length signalLength,//
// with samplingfrequency Fs. Noisedata should be a recording of    //
// noise, related to 'signal'. Noise should have a length of        //
// noiselength and should be of size noiseLength. There are minimum //
// sizes for both datasets. Noise-padding should have already been	//
// applied to signal and noisedata. This implicates that noise- and //
// signallength should be powers of 2.								//
// A windowfile WINDOWFILE, defined in the header, should be present//
// on the system. The window should be of size WINDOWSIZE. In this  //
// case a Hamming window of length 1024 was used. A precalculated   //
// file is used for improved performance.							//
// Postconditions: The filtered signal is stored in output.			//
// The other parameters are note modified. The return value is the  //
// length of 'output'. In some cases, mostly when the length of     //
// the noise or the signal is too short or does not contain enough  //
// information (too much zero-padding). The noise-filter will write //
// an all zero output array. This exception should be caught outside//
// the noisefilter and the program should continue to work with the //
// unfiltered data!													//
// Parameters:														//
// -signal: the zero-padded signal in time domain					//
// -noisedata: a zero-padded recording of noise, in time-domain		//
// -signalLength: the length of signal (power of 2!)				//
// -noiseLength: the length of noise (power of 2!)					//
// -Fs: the sampling frequency of signal and noisedata				//
// -output: a pointer where the result is stored.					//
// Returnvalue: the size of output.									//
//------------------------------------------------------------------//
int noisefilter(float *signal, float* noisedata, int signalLength,
		int noiseLength, int Fs, float **output) {
	//noise filter parameters

	// alpha has been left out in the C-implementation of
	// this noise filter, it is used in the SNR-part of the
	// algorithm. Take a look at the matlab function for more information.
	//float alpha = 0.05;
	float beta = 0.5;
	int beta2 = 1;
	int lambda = 3;

	//---------------------------%
	// Read window file		     %
	//---------------------------%
	FILE * windowFile;
	printf("Reading window file\n");
	windowFile = fopen(WINDOWFILE, "r");
	if (windowFile == 0) {
		printf("Error reading window file.\n");
		return -1;
	}
	int i = 0;
	float window[WINDOWSIZE];
	while (fscanf(windowFile, "%f", &window[i]) == 1) {
		i++;
	}
	fclose(windowFile);
	printf("Windowfile read\n");

	//---------------------------%
	//  Calculate overlap        %
	//---------------------------%
	int overlap = floor(HAMMING_OVERLAP * WINDOWSIZE);
	int noverlap = WINDOWSIZE - overlap;
	int windowCount = floor((noiseLength - noverlap) / (WINDOWSIZE - noverlap));

	//---------------------------%
	// Allocate matrices         %
	//---------------------------%

	//printf("Allocating %d %d for result.\n", windowCount, WINDOWSIZE);
	float **S = allocate2Dfloat(windowCount, WINDOWSIZE); // amplitude
	float **Y = allocate2Dfloat(windowCount, WINDOWSIZE); // imaginary part
	//float *t = (float*) malloc(sizeof(float) * windowCount); // time vector

	//---------------------------%
	// Calculate STFT from noise %
	//---------------------------%
	stft(noisedata, window, noiseLength, noverlap, windowCount, WINDOWSIZE, Fs,
			S, Y); // S & T!!

	//---------------------------%
	// Calculate noise spectrum  %
	//---------------------------%
	float *noise_spectrum = (float*) malloc(sizeof(float) * WINDOWSIZE);

	//	int testdata = 0;
	//	if (testdata == 1) {
	//		printf("Replacing data\n");
	//		fflush(stdout);
	//		for (i = 0; i < windowCount; i++) {
	//			for (j = 0; j < WINDOWSIZE; j++) {
	//				S[i][j]  = 0.5;
	//			}
	//		}
	//	}
	int j = 0;
	float temp;
	for (i = 0; i < WINDOWSIZE; i++) {
		noise_spectrum[i] = 0;
		for (j = 0; j < windowCount; j++) {
			// square of modulus (sqrt and square cancel out)
			temp = pow(S[j][i], 2) + pow(Y[j][i], 2);
			noise_spectrum[i] += temp;
		}
		noise_spectrum[i] /= windowCount;
	}

	// From this point on we start working with the actual recording.
	//---------------------------%
	// Deallocate noise matrix   %
	//---------------------------%
	free2Dfloat(S, windowCount);
	free2Dfloat(Y, windowCount);
	//free(t);
	//t = 0;

	//---------------------------%
	// Calculate window length   %
	//---------------------------%
	windowCount = floor((signalLength - noverlap) / (WINDOWSIZE - noverlap));

	//---------------------------%
	// Allocate Signal matrix    %
	//---------------------------%
	S = allocate2Dfloat(windowCount, WINDOWSIZE);
	Y = allocate2Dfloat(windowCount, WINDOWSIZE);
	//t = (float*) malloc(sizeof(float) * windowCount);

	//---------------------------%
	// Calculate STFT from signal%
	//---------------------------%
	stft(signal, window, signalLength, noverlap, windowCount, WINDOWSIZE, Fs,
			S, Y);

	//	if (testdata == 1) {
	//		printf("Replacing STFT data (signal)\n");
	//		fflush(stdout);
	//		for (i = 0; i < windowCount; i++) {
	//			for (j = 0; j < WINDOWSIZE; j++) {
	//				S[i][j]  = 0.5;
	//			}
	//		}
	//	}
	//---------------------------%
	//       Estimate SNR        %
	//---------------------------%
	printf("Estimating SNR\n");
	fflush(stdout);
	float **absS = allocate2Dfloat(windowCount, WINDOWSIZE);
	printf("Part1\n");

	for (i = 0; i < windowCount; i++) {
		fflush(stdout);
		for (j = 0; j < WINDOWSIZE; j++) {
			// square of modulus (sqrt and square cancel out)
			temp = pow(S[i][j], 2) + pow(Y[i][j], 2);
			absS[i][j] = temp;
		}
	}

	printf("Part2\n");

	float **SNR_est = allocate2Dfloat(windowCount, WINDOWSIZE);
	for (i = 0; i < windowCount; i++) {
		for (j = 0; j < WINDOWSIZE; j++) {
			//printf("noise_spectrum[%f]\n", noise_spectrum[index]);
			SNR_est[i][j] = (absS[i][j] / noise_spectrum[j]) - 1; // a posteriori SNR
			if (SNR_est[i][j] < 0) {
				SNR_est[i][j] = 0;
			}
			//printf("SNR %d %d: %e\n", i, j, SNR_est[i][j]);
		}
	}

	// We dont need the noise spectrum anymore, free!
	free(noise_spectrum);

	//---------------------------%
	//  Compute attenuation map  %
	//---------------------------%
	printf("Computating attenuation map\n");
	float **atMap = allocate2Dfloat(windowCount, WINDOWSIZE);
	float **STFT = allocate2Dfloat(windowCount, WINDOWSIZE);
	for (i = 0; i < windowCount; i++) { // --> OK!
		for (j = 0; j < WINDOWSIZE; j++) {
			atMap[i][j] = pow(1 - (lambda
					* pow((1 / (SNR_est[i][j] + 1)), beta)), beta2);
			if (atMap[i][j] < 0) {
				atMap[i][j] = 0;
			}
			STFT[i][j] = atMap[i][j] * S[i][j];
			Y[i][j] = atMap[i][j] * Y[i][j];
		}
	}

	//--------------------------%
	//   Compute Inverse STFT   %
	//--------------------------%
	printf("Computing Inverse STFT: \n");
	int ind[WINDOWSIZE];
	for (i = 0; i < WINDOWSIZE; i++) {
		ind[i] = i;
	}

	//Check malloc size of result!
	printf("allocating: %d %d %d %d\n", windowCount, overlap, WINDOWSIZE,
			windowCount * overlap + WINDOWSIZE);

	float *y = (float*) malloc(sizeof(float) * WINDOWSIZE);
	for (i = 0; i < WINDOWSIZE; i++) {
		y[i] = 0.0;
	}
	int m = nextPow(WINDOWSIZE);

	//clear the output signal
	*output = (float*) malloc(sizeof(float) * signalLength);

	for (i = 0; i < signalLength; i++) {
		(*output)[i] = 0.0;
	}

	//Overlapp add technique
	int left_index;
	for (i = 0; i < windowCount; i++) {
		//printf("iFFT %d\n", i);
		fflush(stdout);
		FFT(-1, m, STFT[i], Y[i]);
		left_index = (i * overlap);
		for (j = 0; j < WINDOWSIZE; j++) {
			(*output)[left_index + j] += STFT[i][j];// * window[j];
		}
	}

	free2Dfloat(absS, windowCount);
	free2Dfloat(SNR_est, windowCount);
	free2Dfloat(STFT, windowCount);
	free2Dfloat(S, windowCount);
	S = 0;
	absS = 0;
	SNR_est = 0;
	STFT = 0;
	//free(t);
	//t = 0;
	return signalLength;
}

void sinetest(float *data, int signalLength) {
	//signal window parameters
	FILE * pFile;
	printf("Reading window file\n");
	pFile = fopen(WINDOWFILE, "r");
	int i = 0;
	float window[WINDOWSIZE];

	while (fscanf(pFile, "%f", &window[i]) == 1) {
		i++;
	}
	fclose(pFile);
	printf("Windowfile read");
	int overlap = floor(HAMMING_OVERLAP * WINDOWSIZE);
	//Signal parameters
	// size(t) -> 1 x #windows
	// size(S) -> WINDOW_SIZE x #windows

	int noverlap = WINDOWSIZE - overlap;
	int windowCount = floor((32768 - noverlap) / (WINDOWSIZE - noverlap));
	//printf("Allocating %d %d for result.\n", windowCount, WINDOWSIZE);
	float **S = allocate2Dfloat(windowCount, WINDOWSIZE);
	float **Y = allocate2Dfloat(windowCount, WINDOWSIZE);
	//float *t = (float*) malloc(sizeof(float) * windowCount);

	printf("STFT\n");
	stft(data, window, 32768, noverlap, windowCount, WINDOWSIZE, FS, S, Y);

	printf("-> Step 5/5: Compute Inverse STFT: \n");
	int ind[WINDOWSIZE];
	for (i = 0; i < WINDOWSIZE; i++) {
		ind[i] = i;
	}
	//Check malloc size of result!

	printf("allocating: %d %d %d %d\n", windowCount, overlap, WINDOWSIZE,
			windowCount * overlap + WINDOWSIZE);

	int m = nextPow(WINDOWSIZE);

	//clear the original signal
	//float test[1024];
	for (i = 0; i < signalLength; i++) {
		data[i] = 0.0;
		//test[i%1024] = 0.5;
	}
	int j;
	int left_index;
	//Overlapp add technique
	for (i = 0; i < windowCount; i++) {
		printf("iFFT %d\n", i);
		fflush(stdout);
		FFT(-1, m, S[i], Y[i]);
		left_index = (i * overlap);
		for (j = 0; j < WINDOWSIZE; j++) {
			data[left_index + j] += S[i][j];// * window[j];
		}
	}
	printf("Noisefiltering Complete.\n");
}
