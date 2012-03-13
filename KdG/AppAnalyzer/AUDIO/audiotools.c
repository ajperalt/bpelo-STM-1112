/*
 * audiotools.c
 *
 *  Created on: May 20, 2011
 *      Author: Siegfried Mercelis
 */

#include <stdio.h>

//-----------------------max(data,start,end)------------------------//
// Helper function to determine the absolute peak value             //
// Parameters:                                                      //
//   -data: array of data to be searched (index position = 0)       //
//   -start: start index of search                                  //
//   -end: end index of search (must be smaller than size of array!)//
// Return value: index of maximum in data-array relative to 0, not  //
//  to the value submitted with parameter start!                    //
//------------------------------------------------------------------//
int max(float* data, int start, int end) {
	int i;
	int maxpos = -1;
	float val;
	float max = 0.0;
	for (i = start; i < end; i++) {
		val = data[i];

		if (val < 0) {
			val = -val;
		}
		if (val > max) {
			max = val;
			maxpos = i;
		}
	}
	return maxpos;
}

//--------------------normalize(data,length)------------------------//
// Searches the data for the highest peak and scales the matrix.    //
// The result is a datase twhere the highest peak equals to +1 or -1//
// Parameters:                                                      //
//   -data: array of data to be searched (index position = 0)       //
//   -length: size of the array to be searched and adjusted			//
// Post-condition: the data-array is modified.                		//
//------------------------------------------------------------------//
void normalize(float *data, int length) {
	float maximum = data[max(data, 0, length)];
	float factor = 1 / maximum;
	int i;
	printf("nmaj: %f\n", maximum);
	for (i = 0; i < length; i++) {
		data[i] = data[i] * factor;
	}
}

int nextPow(int N) {
	int m = 1;
	int NFFT = 2;
	while (NFFT < N) {
		NFFT = NFFT << 1;
		m++;
		if (NFFT < 0) {
			printf("Error calculating nextpow\n");
			return -1;
		}
	}
	return m;
}
