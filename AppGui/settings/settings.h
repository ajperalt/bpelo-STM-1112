/*
 * settings.h
 *
 *  Created on: May 19, 2011
 *      Author: philip
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

/**
 * \file settings.h
 *
 * \brief Has some functions
 */

#include "../../includes/gui/settings/sapim_gui_settings_structs.h"
#include "../../includes/gui/settings/sapim_gui_settings_constants.h"

/**
 * \brief Load standard settings
 *
 * You should always call this function in the beginning/initialization of the program.
 */
void initSettings();

/**
 * \brief Return a copy of the audio settings
 *
 * A copy is returned so you can change the values. Afterwards you can store them with setAudioSettings(...)
 *
 * @return A copy of the settings
 */
AUDIO_SETTINGS getAudioSettingsCopy();

/**
 * \brief Return a constant reference of the audio settings.
 *
 * The const means that you shouldn't change the settings this way. This function returns a struct has a read-only purpose.
 *
 * @return A reference to the audio settings.
 */
const AUDIO_SETTINGS* getAudioSettingsReference();

/**
 * \brief Change the audio settings to the new settings.
 *
 *  The values found in the reference are copied to the \a audioSettings in settings.c. This means settings doesn't need to be kept on the heap.
 *
 *  @param settings A reference to the new settings.
 */
void setAudioSettings(AUDIO_SETTINGS* settings);

/**
 * \brief Return a copy of the mechanic settings
 *
 * A copy is returned so you can change the values. Afterwards you can store them with setMechanicSettings(...)
 *
 * @return A copy of the settings
 */
MECHANIC_SETTINGS getMechanicSettingsCopy();

/**
 * \brief Return a constant reference of the mechanic settings.
 *
 * The const means that you shouldn't change the settings this way. This function returns a struct that has a read-only purpose.
 *
 * @return A reference to the mechanic settings.
 */
const MECHANIC_SETTINGS* getMechanicSettingsReference();

/**
 * \brief Change the mechanic settings to the new settings.
 *
 * The values found in the reference are copied to the \a mechanicSettings in settings.c. This means settings doesn't need to be kept on the heap.
 * Only the values that belongs to \a type in the struct are copied.
 *
 * @param settings A reference to the new settings.
 */
void setMechanicSettings(MECHANIC_SETTINGS* settings);

#endif /* SETTINGS_H_ */
