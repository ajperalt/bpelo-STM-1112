/*
 * filter.c
 *
 *  Created on: May 20, 2011
 *      Author: Siegfried Mercelis
 */
// IIR-filter
// Source: http://www-users.cs.york.ac.uk/~fisher/mkfilter/

#include <stdio.h>

#define NZEROS 10
#define NPOLES 10
#define GAIN   9.959377903e+04

float filter_helper(float input);
float xv[NZEROS + 1], yv[NPOLES + 1];

void filter(float *data, int length) {
	int i;
	printf("start filter\n");
	for (i = 0; i < length; i++) {
		data[i] = filter_helper(data[i]);
	}
	printf("Filter complete");
}

float filter_helper(float input) {
	xv[0] = xv[1];
	xv[1] = xv[2];
	xv[2] = xv[3];
	xv[3] = xv[4];
	xv[4] = xv[5];
	xv[5] = xv[6];
	xv[6] = xv[7];
	xv[7] = xv[8];
	xv[8] = xv[9];
	xv[9] = xv[10];
	xv[10] = input / GAIN;
	yv[0] = yv[1];
	yv[1] = yv[2];
	yv[2] = yv[3];
	yv[3] = yv[4];
	yv[4] = yv[5];
	yv[5] = yv[6];
	yv[6] = yv[7];
	yv[7] = yv[8];
	yv[8] = yv[9];
	yv[9] = yv[10];
	yv[10] = (xv[10] - xv[0]) + 5 * (xv[2] - xv[8]) + 10 * (xv[6] - xv[4])
			+ (-0.4999609370 * yv[0]) + (5.2096158756 * yv[1])
			+ (-24.5846947520 * yv[2]) + (69.1860472780 * yv[3])
			+ (-128.5737953200 * yv[4]) + (164.8628075800 * yv[5])
			+ (-147.7114496000 * yv[6]) + (91.3126506390 * yv[7])
			+ (-37.2739028920 * yv[8]) + (9.0726818846 * yv[9]);
	return yv[10];
}
