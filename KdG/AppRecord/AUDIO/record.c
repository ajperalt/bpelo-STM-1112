#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "include/PortAudio/portaudio.h"
#include "include/record.h"

int record(int recordLength, int numChannels, int sampleRate, char* fileName) {
    if (recordLength <= 0) {
	printf("Error, duration too short.");
	return -1;}
    PaStreamParameters inputParameters;//, outputParameters;
    PaStream *stream;
    PaError err;
    SAMPLE *recordedSamples;
    int i;
    int totalFrames;
    int numSamples;
    int numBytes;
    SAMPLE max, average, val;

    totalFrames = recordLength; /* Record for a few seconds. */
    numSamples = totalFrames * numChannels;

    numBytes = numSamples * sizeof(SAMPLE);

    recordedSamples = (SAMPLE *) malloc( numBytes );

    if( recordedSamples == NULL ){
        printf("Could not allocate record array.\n");
        exit(1);}
    for( i=0; i<numSamples; i++ ) recordedSamples[i] = 0;

    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    if (inputParameters.device == paNoDevice) {
      fprintf(stderr,"Error: No default input device.\n");
      return -1;
    }
    inputParameters.channelCount = numChannels;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    /* Record some audio. -------------------------------------------- */
    err = Pa_OpenStream(
              &stream,
              &inputParameters,
              NULL,                  /* &outputParameters, */
              sampleRate,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              NULL, /* no callback, use blocking API */
              NULL ); /* no callback, so no callback userData */
    if( err != paNoError ) return -1;

    err = Pa_StartStream( stream );
    if( err != paNoError ) return -1;
    printf("Now recording!!\n"); fflush(stdout);
    //enable(GPIO_SOLENOID);
    err = Pa_ReadStream( stream, recordedSamples, totalFrames );
    if( err != paNoError ) return -1;

    err = Pa_CloseStream( stream );
    if( err != paNoError ) return -1;

    /* Measure maximum peak amplitude. */
    max = 0;
    average = 0;
    for( i=0; i<numSamples; i++ )
    {
        val = recordedSamples[i];
        if( val < 0 ) val = -val; /* ABS */
        if( val > max )
        {
            max = val;
        }
        average += val;
    }

    average = average / numSamples;

    printf("Sample max amplitude = "PRINTF_S_FORMAT"\n", max );
    printf("Sample average = "PRINTF_S_FORMAT"\n", average );
    /* Write recorded data to a file. */
	FILE  *fid;
	fid = fopen(fileName, "wb");
	if( fid == NULL )
	{
		printf("Could not open file for RECORD.\n");
	}
	else
	{
		fwrite( recordedSamples, numChannels * sizeof(SAMPLE), totalFrames, fid );
		fclose( fid );
		printf("Wrote data to %s\n", fileName);
	}

//    /* Playback recorded data.  -------------------------------------------- */
//
//    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
//    if (outputParameters.device == paNoDevice) {
//      fprintf(stderr,"Error: No default output device.\n");
//      goto error;
//    }
//    outputParameters.channelCount = numChannels;
//    outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
//    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
//    outputParameters.hostApiSpecificStreamInfo = NULL;
//
//    printf("Begin playback.\n"); fflush(stdout);
//    err = Pa_OpenStream(
//              &stream,
//              NULL, /* no input */
//              &outputParameters,
//              sampleRate,
//              FRAMES_PER_BUFFER,
//              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
//              NULL, /* no callback, use blocking API */
//              NULL ); /* no callback, so no callback userData */
//    if( err != paNoError ) goto error;
//
//    if( stream )
//    {
//        err = Pa_StartStream( stream );
//        if( err != paNoError ) goto error;
//        printf("Waiting for playback to finish.\n"); fflush(stdout);
//
//        err = Pa_WriteStream( stream, recordedSamples, totalFrames );
//        if( err != paNoError ) goto error;
//
//        err = Pa_CloseStream( stream );
//        if( err != paNoError ) goto error;
//        printf("Done.\n"); fflush(stdout);
//    }
    free( recordedSamples );

    //Pa_Terminate();
    return 0;

//error:
//    //Pa_Terminate();
////error2:
//    printf( "An error occured while using the portaudio stream\n" );
//    printf( "Error number: %d\n", err );
//    printf( "Error message: %s\n", Pa_GetErrorText( err ) );
//    return -1;
}
