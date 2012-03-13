/*
 * main.c
 *
 *  Created on: May 20, 2011
 *      Author: Siegfried Mercelis
 */
#include <stdio.h>
#include <stdlib.h>
#include "AUDIO/include/analyze.h"
#include "AUDIO/include/read_audio.h"

int main(void) {
	printf("\n\n---------------------------\n");
	printf("| STARTING AUDIO ANALYSIS |\n");
	printf("---------------------------\n");
	//---------------------------%
	// Variables 				 %
	//---------------------------%
	//recording parameters
	char *fileName = "audio.raw";
	char *noiseFile = "noisedata.raw";
	float *signal = 0;
	float *noise = 0;
	int enableNoisefilter = 1;
	//fft parameters
	frequency_data frequency;

	//---------------------------%
	// Variables 				 %
	//---------------------------%
	int signalLength = read_audio(fileName, &signal);
	int noiseLength = read_audio(noiseFile, &noise);
	if (signalLength <= 0) {
		printf("Error reading signal file. Terminating.\n");
		return -1;
	}
	if (noiseLength <= 0) {
		printf("No noise file found, turning of noisefilter.\n");
		enableNoisefilter = 0;
	}

	if (getFrequency(signal, signalLength, noise, noiseLength, &frequency,
			enableNoisefilter) < 0) {
		printf("Error calculating frequency... Terminating\n");
		return -1;
	} else {
		printf("The recorded frequency is: %.2f with precision %.2f\n",
				frequency.frequency, frequency.precision);
		printf("Writing output files.");
		FILE *fOutput = fopen("analyzer_output.dat", "wb");
		fwrite(&frequency, sizeof(frequency_data), 1, fOutput);
		fclose(fOutput);
		fOutput = 0;

		//WRITE THE FILE TO DISK!
	}
	free(signal);
	free(noise);
	printf("\nDone with everything. \nEND OF AUDIO ANALYSIS.\n");
	return 0;
}
