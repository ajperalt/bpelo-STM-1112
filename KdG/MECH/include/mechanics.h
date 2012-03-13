#ifndef MECHANICS_H_INCLUDED
#define MECHANICS_H_INCLUDED

#include <math.h>
#include <stdio.h>
#include "../../includes/mechanics/sapim_mech_structs.h"


/**
 * \file mechanics.h
 *
 * \brief Lists some defines and functions
 */

// #define PI 3.14159265
#define MINFORCE 0      ///< Minimal force used in iteration, result should be higher than this value!
#define MAXFORCE 5000   ///< Maximal force used in iteration, result should be lower than this value!
#define MAXOFFSET 0.1   ///< Maximal difference between measured frequency and calculated frequency. Iteration will stop when the difference is lower than this value.
#define MAXITERATIONS 100  ///< Maximal amount of times the algorithm is allowed to iterate

/**
 * \brief Calculate the force from the frequency and spoke data
 *
 * @param spoke Data about the selected spoke
 * @param frequency Data about the frequency found
 * @param force Here we will store the resulting force
 * @return 0 on success
 */
int getForce(spoke_data* spoke, frequency_data* frequency, force_data* force);
#endif // MECHANICS_H_INCLUDED
