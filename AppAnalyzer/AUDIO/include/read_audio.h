#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

/**
 * \file read_audio.h
 *
 * \brief Has some functions
 */

/**
 * \brief Reads the data from \a filename and store it in \a buffer
 *
 * @param fileName The path to the audio file
 * @param buffer A pointer where we will store the data. This buffer will be allocated in this function!
 *
 * @waring \a buffer will be allocated inside this function. If you pass a pointer to this function, be sure it has been freed.
 */
int read_audio(char *fileName, float** buffer);

#endif // AUDIO_H_INCLUDED
