/*
 * settings.c
 *
 *  Created on: May 19, 2011
 *      Author: philip
 */

#include "settings.h"
#include "../../includes/gui/settings/sapim_gui_settings.h"

AUDIO_SETTINGS audioSettings;
MECHANIC_SETTINGS mechanicSettings;

void initSettings() {
	audioSettings.noisefilterEnabled = SETTINGS_FALSE;
	mechanicSettings.type = 0;
}

AUDIO_SETTINGS getAudioSettingsCopy() {
	return audioSettings;
}

const AUDIO_SETTINGS* getAudioSettingsReference() {
	return &audioSettings;
}

void setAudioSettings(AUDIO_SETTINGS* newSettings) {
	audioSettings.noisefilterEnabled = newSettings->noisefilterEnabled;
}


MECHANIC_SETTINGS getMechanicSettingsCopy() {
	return mechanicSettings;
}

const MECHANIC_SETTINGS* getMechanicSettingsReference() {
	return &mechanicSettings;
}

void setMechanicSettings(MECHANIC_SETTINGS* settings) {
	mechanicSettings.type = settings->type;

	switch(settings->type) {
	case MECHANIC_FLAT:
		mechanicSettings.flat.width = settings->flat.width;
		mechanicSettings.flat.height = settings->flat.height;
		break;
	case MECHANIC_OVAL:
		mechanicSettings.oval.diameterX = settings->oval.diameterX;
		mechanicSettings.oval.diameterY = settings->oval.diameterY;
		break;
	case MECHANIC_ROUND:
		mechanicSettings.round.diameter = settings->round.diameter;
		break;
	case MECHANIC_ROUNDRECT:
		mechanicSettings.roundrect.width = settings->roundrect.width;
		mechanicSettings.roundrect.height = settings->roundrect.height;
		break;
	}
}
