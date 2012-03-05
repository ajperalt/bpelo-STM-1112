#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "include/read_audio.h"
#include "../../AppRecord/AUDIO/include/record.h"

//returns array length
int read_audio(char *fileName, SAMPLE** buffer) {
    int numSamples;
    long lSize;
    FILE  *pFile;
    size_t result;

    pFile = fopen(fileName, "rb");
	if( pFile == NULL )
	{
		printf("Could not open file for READ.\n");
		return -1;
	}
	else
	{
	    fseek (pFile , 0 , SEEK_END);
	    lSize = ftell (pFile);//number of bytes
	    rewind (pFile);
	    // allocate memory to contain the whole file:
	    *buffer = (SAMPLE*) malloc (sizeof(SAMPLE)*lSize);
	    if (*buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

	    // read from file
	    numSamples = lSize/sizeof(SAMPLE);
	    result = fread (*buffer,sizeof(SAMPLE),numSamples,pFile);
	    if (result != numSamples) {fputs ("Reading error",stderr); exit (3);}

		fclose( pFile );
		printf("Read %s (%d samples)\n",fileName, numSamples);
	}
    return numSamples;
}
