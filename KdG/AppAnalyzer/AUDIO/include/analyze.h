/**
 * analyze.h
 *
 *  Created on: May 20, 2011
 *      Author: Siegfried Mercelis
 */

#ifndef ANALYZE_H_
#define ANALYZE_H_

/**
 * \file analyze.h
 *
 * \brief Has some defines, structs and functions
 */

/**
 * Sampling frequency
 */
#define FS 44100

/**
 * \struct frequency_data
 *
 * \brief A struct which hold data about the found frequency.
 */
typedef struct {
    float frequency;	/**< The frequency */
    float precision;	/**< The precision of the frequency */
} frequency_data;

/**
 * \brief Search the frequency in the data
 * Returns the frequency found in the data.
 *
 * @param data The data in which the function search for the frequency
 * @param signalLength The length of the signal in samples
 * @param noiseData The data of noise, this could help to find the frequency more accurate.
 * @param noiseDuration The duration of the noise data in samples
 * @param result A pointer in which we will put the frequency we've found
 * @param noisefilter_enabled Is the noise filter used (\a noisefilter_enabled = 1) or not (\a noisefilter_enabled = 0)?
 * @return 0 on success
 *
 * @waring The function will change \a result
 */
int getFrequency(float* data, int signalLength, float *noiseData,
		int noiseDuration, frequency_data* result, int noisefilter_enabled);



#endif /* ANALYZE_H_ */
