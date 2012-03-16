#include "meting.h"
#include "AUDIO/include/record.h"

Meting::Meting()
{
	err = record(int recordLength, int numChannels, int sampleRate, char* fileName)
	record(meting);
	frequency = timeToFrequency(meting);
	force = frequencyToForce(frequency);
}

Meting::~Meting(){}

unsigned float meting(){
	return meting;
}
int timeToFrequency(){
	return timeToFrequency;
}
int frequency(){
	return frequency;
}
int frequencyToForce(){
	return frequencyToForce;
}
int force(){
	return force;
}

bool meting(unsigned float meting){
	self.meting = meting;
	return TRUE;
}
bool timeToFrequency(int timeToFrequency){
	self.timeToFrequency = timeToFrequency;
	return TRUE;
}
bool frequency(int frequency){
	self.frequency = frequency;
	return TRUE;
}
bool frequencyToForce(int frequencyToForce){
	self.frequencyToForce = frequencyToForce;
	return TRUE;
}