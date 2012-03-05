/*
 * app.c
 *
 *  Created on: May 20, 2011
 *      Author: philip
 */
#include <stdio.h>
#include <stdlib.h>

#include "../includes/gui/settings/sapim_gui_settings.h"

#include "include/mechanics.h"
#include "../includes/mechanics/sapim_mech_structs.h"
#include "../AppGui/settings/settings.h"

int main() {
	MECHANIC_SETTINGS mechSettings;
	spoke_data spokeData;
	frequency_data frequency;
	force_data forceData;
	FILE *output = 0;
	FILE *input = fopen("workspace/mechanics_inputs.dat", "rb");
	if(!input) {
		printf("No file found for mechanics input!\n");
		return -1;
	}

	fread(&mechSettings, sizeof(MECHANIC_SETTINGS), 1, input);
	fclose(input);

	input = fopen("workspace/analyzer_output.dat", "rb");
	if(!input) {
		printf("No frequency input file found!\n");
		return -2;
	}

	fread(&frequency, sizeof(frequency_data), 1, input);
	fclose(input);

	printf("Frequency: %lf\n", frequency.frequency);

	spokeData.type = mechSettings.type;
	spokeData.length = 0.08;
	spokeData.elasticity = 196E9;
	spokeData.density = 7849;
	// correction factor for 14G276 2mm
	//spokeData.correction = 1.460418701171875;
	//spokeData.correction = 1.475;
	//spokeData.correction = 1.450;
	spokeData.correction = 1.4694;

	printf("Mech settings:\n");
	printf("Type: %d\n", mechSettings.type);
	printf("Diameter: %f\n", mechSettings.round.diameter);

	switch(spokeData.type) {
	case MECHANIC_FLAT:
		spokeData.majorAxis = mechSettings.flat.width / 1000;
		spokeData.minorAxis = mechSettings.flat.height / 1000;
		break;
	case MECHANIC_ROUND:
		spokeData.majorAxis = mechSettings.round.diameter / 1000;
		break;
	case MECHANIC_OVAL:
		spokeData.majorAxis = mechSettings.oval.diameterX / 1000;
		spokeData.minorAxis = mechSettings.oval.diameterY / 1000;
		break;
	case MECHANIC_ROUNDRECT:
		spokeData.majorAxis = mechSettings.roundrect.width / 1000;
		spokeData.minorAxis = mechSettings.roundrect.height / 1000;
		break;
	default:
		return -3;
	}

	getForce(&spokeData, &frequency, &forceData);

	output = fopen("workspace/result.dat", "wb");
	if(!output) {
		printf("Couldn't write the result!\n");
		return -4;
	}

	fwrite(&forceData, sizeof(force_data), 1, output);
	fclose(output);

	return 0;
}
