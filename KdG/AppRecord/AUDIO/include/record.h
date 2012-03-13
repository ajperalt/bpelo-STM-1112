#ifndef RECORD_H
#define RECORD_H

/**
 * \file record.h
 *
 * \brief Has some functions and defines
 */

/**
 * \brief Record audio from the line-in
 *
 * @param recordLength The length you want to record (in frames)
 * @param numChannels The number of channels used
 * @param sampleRate The sampling rate
 * @param fileName The file where to store the data
 * @return 0 on success
 */
int record(int recordLength, int numChannels, int sampleRate, char* fileName);

/* #define sampleRate  (17932) // Test failure to open with this value. */
//#define sampleRate  (44100)
#define FRAMES_PER_BUFFER (1024)
//#define NUM_SECONDS     (5)
//#define NUM_CHANNELS    (1)
/* #define DITHER_FLAG     (paDitherOff)  */
#define DITHER_FLAG     (0) /**/

/* Select sample format. */
#if 1
  #define PA_SAMPLE_TYPE  paFloat32
  typedef float SAMPLE;
  #define SAMPLE_SILENCE  (0.0f)
  #define PRINTF_S_FORMAT "%.8f"
#elif 1
  #define PA_SAMPLE_TYPE  paInt16
  typedef short SAMPLE;
  #define SAMPLE_SILENCE  (0)
  #define PRINTF_S_FORMAT "%d"
#elif 0
  #define PA_SAMPLE_TYPE  paInt8
  typedef char SAMPLE;
  #define SAMPLE_SILENCE  (0)
  #define PRINTF_S_FORMAT "%d"
#else
  #define PA_SAMPLE_TYPE  paUInt8
  typedef unsigned char SAMPLE;
  #define SAMPLE_SILENCE  (128)
  #define PRINTF_S_FORMAT "%d"
#endif
#define PI 3.14159265
#endif
