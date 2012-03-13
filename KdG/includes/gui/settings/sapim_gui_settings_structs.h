/*
 * sapim_gui_settings_structs.h
 *
 *  Created on: May 20, 2011
 *      Author: philip
 */

#ifndef SAPIM_GUI_SETTINGS_STRUCTS_H_
#define SAPIM_GUI_SETTINGS_STRUCTS_H_

/**
 * \file sapim_gui_settings_structs.h
 *
 * \brief Lists some structs used by settings
 */

/**
 * \struct ROUND_SETTINGS
 *
 * A struct that holds the parameters for round spokes
 */
typedef struct {
	float diameter; /**< The diameter of the spoke */
} ROUND_SETTINGS;

/**
 * \struct OVAL_SETTINGS
 *
 * A struct that holds the parameters for oval spokes
 */
typedef struct {
	float diameterX; /**< The horizontal diameter of the spoke */
	float diameterY; /**< The vertical diameter of the spoke */
} OVAL_SETTINGS;

/**
 * \struct FLAT_SETTINGS
 *
 * A struct that holds the parameters for flat spokes
 */
typedef struct {
	float width; /**< The width of the spoke */
	float height; /**< The height of the spoke */
} FLAT_SETTINGS;

/**
 * \struct ROUNDRECT_SETTINGS
 *
 * A struct that holds the parameters for rounded rectangle spokes
 */
typedef struct {
	float width; /**< The width of the spoke */
	float height; /**< The height of the spoke */
} ROUNDRECT_SETTINGS;

/**
 * \struct AUDIO_SETTINGS
 *
 * A struct that holds the audio settings parameters.
 */
typedef struct {
	char noisefilterEnabled; /**< SETTINGS_TRUE if the filter is enabled, else SETTINGS_FALSE */
} AUDIO_SETTINGS;

/**
 * \struct MECHANIC_SETTINGS
 *
 * A struct that holds the mechanical settings. Which substruct needs to be used can be found in \a type.
 */
typedef struct {
    /**
     * \var type
     *
     * \brief This variable holds which substruct should be used.
     *
     * The values are defined in sapim_gui_settings_constants.h
     * \a MECHANIC_NONE : There is no substruct selected
     * \a MECHANIC_ROUND : The values in \a round are set
     * \a MECHANIC_FLAT : The values in \a flat are set
     * \a MECHANIC_OVAL : The values in \a oval are set
     * \a MECHANIC_ROUNDRECT : The values in \a roundrect are set
     */
	char type;

	ROUND_SETTINGS round; /**< Holds the information about round spokes if type == \a MECHANIC_ROUND */
	FLAT_SETTINGS flat; /**< Holds the information about flat spokes if type == \a MECHANIC_FLAT */
	OVAL_SETTINGS oval; /**< Holds the information about oval spokes if type == \a MECHANIC_OVAL */
	ROUNDRECT_SETTINGS roundrect; /**< Holds the information about rounded rectangle spokes if type == \a MECHANIC_ROUNDRECT */
} MECHANIC_SETTINGS;

#endif /* SAPIM_GUI_SETTINGS_STRUCTS_H_ */
