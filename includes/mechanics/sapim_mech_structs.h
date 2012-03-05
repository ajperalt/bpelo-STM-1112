/*
 * sapim_mech_structs.h
 *
 *  Created on: May 20, 2011
 *      Author: philip
 */

#ifndef SAPIM_MECH_STRUCTS_H_
#define SAPIM_MECH_STRUCTS_H_


/**
 * \file sapim_mech_structs.h
 *
 * \brief The public structs, used by the mechanic application
 */

/**
 * \struct spoke_data
 *
 * \brief Has all information about the spoke
 */
typedef struct {
    int type; ///< could be any of the MECHANIC_ constants in sapim_gui_settings_constants.h
    float length;
    float minorAxis; ///< smallest axis by oval, height by flat and roundrect
    float majorAxis; ///< largest axis by oval, width by flat and roundrect, radius by round
    float area;
    float elasticity;
    float density;
    float mass;
    float volume;
    float inertia;
    float correction;
} spoke_data;

/**
 * \struct frequencydata
 *
 * \brief A struct that holds data about the found frequency
 */
typedef struct {
	float frequency;
	float precision;
} frequency_data;

/**
 * \struct force_data
 *
 * \brief A struct that holds data about the force the Mechanic application has found
 */
typedef struct {
    int iterations;
    float force;
    float offset;
} force_data;


#endif /* SAPIM_MECH_STRUCTS_H_ */
