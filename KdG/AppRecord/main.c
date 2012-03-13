#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AUDIO/include/PortAudio/portaudio.h"
#include "AUDIO/include/record.h"

#define aantalPulsen 3

int main(int argc, char **args) {
    int err;
    int i;
    if (aantalPulsen < 1) {
	printf("fout"); return -1;}
	
    for (i = 0 ; i < aantalPulsen ; i++) {	//incompleet

    char fileName[256];
    if (argc == 2) {
	printf("Recording %s.\n", args[1]);
	fflush(stdout);
//	strncpy(fileName,args[1],strlen(args[1]) +1);
//	strncat(fileName,(char*)i,1);

	sprintf(fileName, "%s%d.raw", args[1], i);


	printf("Recording %s.\n", fileName);
	fflush(stdout);}
    else {
	printf("Error. No path set in arguments. %d\n", argc);
	return -1;}
    
    err = Pa_Initialize(); // hier wordt portaudio geïnitialiseerd
    
    if( err != paNoError ) {
	printf("Error initializing audio.\n");
	return -1;}
    if (record(16384, 1, 44100,fileName) < 0) {  //seconds, channels, samplerate, filename
		printf("Error recording audio!!!\nTerminating.\n");
		Pa_Terminate();
		return -1;}
    printf("Recording completed. Terminating\n");
    Pa_Terminate();} // portaudio beëindigd!
    return 0;}





