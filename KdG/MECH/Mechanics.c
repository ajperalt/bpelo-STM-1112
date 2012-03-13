#include <math.h>

#include "../includes/gui/settings/sapim_gui_settings.h"

#include "include/mechanics.h"
#include "../includes/mechanics/sapim_mech_structs.h"

double inertia_oval(double majorAxis, double minorAxis) {
	return (M_PI / 64) * majorAxis * minorAxis * minorAxis * minorAxis;
}
double inertia_rectangle(double majorAxis, double minorAxis) {
	return (majorAxis * minorAxis * minorAxis * minorAxis) / 12;
}
double inertia_circle(double majorAxis) {
	//Area moment of inertia pi/64*diameter^4 [m^4]
	return (M_PI / 4) * pow(majorAxis / 2, 4);
}
double area_oval(double majorAxis, double minorAxis) {
	return (M_PI / 4) * minorAxis * majorAxis;
}
double area_rectangle(double majorAxis, double minorAxis) {
	return minorAxis * majorAxis;
}
double area_circle(double majorAxis) {
	return M_PI * (majorAxis / 2) * (majorAxis / 2);
}

int calculate_mechanical_properties(spoke_data* spoke) {
	if ((spoke->density < 0) || (spoke->elasticity < 0)) {
		return -1;
	}
	switch (spoke->type) {
	case MECHANIC_ROUND:
		printf("Spoke is round\n");
		spoke->area = area_circle(spoke->majorAxis);
		spoke->inertia = inertia_circle(spoke->majorAxis);
		break;
	case MECHANIC_OVAL:
		printf("Spoke is oval\n");
		spoke->area = area_oval(spoke->majorAxis, spoke->minorAxis);
		spoke->inertia = inertia_oval(spoke->majorAxis, spoke->minorAxis);
		break;
	case MECHANIC_ROUNDRECT:
		printf("Spoke is a rounded rectangle\n");
		spoke->area = (area_oval(spoke->majorAxis, spoke->minorAxis)
				+ area_rectangle(spoke->majorAxis, spoke->minorAxis)) / 2;
		spoke->inertia = (inertia_oval(spoke->majorAxis, spoke->minorAxis)
				+ inertia_rectangle(spoke->majorAxis, spoke->minorAxis)) / 2;
		break;
	case MECHANIC_FLAT:
		printf("Spoke is flat\n");
		spoke->area = (0.2 * area_oval(spoke->majorAxis, spoke->minorAxis)
				+ 0.8 * area_rectangle(spoke->majorAxis, spoke->minorAxis));
		spoke->inertia = (0.2
				* inertia_oval(spoke->majorAxis, spoke->minorAxis) + 0.8
				* inertia_rectangle(spoke->majorAxis, spoke->minorAxis));
		break;
		/*case MECHANIC_CUSTOM:
		 //all data has been entered by the user, no calculations required
		 return 0;*/
	default:
		return -1;
	}
	spoke->volume = spoke->area * spoke->length; //%pi*r²*heigth in m³
	spoke->mass = spoke->density * spoke->volume; //  %mass in kg
	return 0;
}

float freqFromForce(spoke_data* spoke, float N) {
	float k = sqrt(N / (spoke->elasticity * spoke->inertia));
	float b = k * spoke->length / 4;
	float a = k * N / (b - tanh(b));
	return (1 / (2 * M_PI)) * sqrt(a / spoke->mass);
}

int getForce(spoke_data* spoke, frequency_data* frequency, force_data* force) {
	if (calculate_mechanical_properties(spoke) < 0) {
		return -1;
	}
	//RANGE
	float min = MINFORCE;
	float max = MAXFORCE;
	//ITERATION VARIABLES
	force->offset = max;
	force->iterations = 0;
	while ((force->offset > MAXOFFSET) && (force->iterations < MAXITERATIONS)) {
		force->force = min + (max - min) / 2;
		float iterFreq = freqFromForce(spoke, force->force) * spoke->correction;
		if (iterFreq == frequency->frequency) {
			break;
		} else if (iterFreq > frequency->frequency) {
			printf("%f > %f --> %f\n", iterFreq, frequency->frequency,
					force->force);
			max = max - (max - min) / 2;
		} else {
			printf("Spoke info:\n");
			printf("Length: %f\n", spoke->length);
			printf("Elast: %f\n", spoke->elasticity);
			printf("Dens: %f\n", spoke->density);
			printf("Type: %d\n", spoke->type);
			printf("Area: %f\n", spoke->area);
			printf("Type: %d\n", spoke->type);
			printf("Intertia: %f\n", spoke->inertia);
			printf("Correction: %f\n", spoke->correction);

			printf("%f < %f --> %f\n", iterFreq, frequency->frequency,
					force->force);
			min = min + (max - min) / 2;
		}
		force->iterations++;
		force->offset = fabs(frequency->frequency - iterFreq);
	}
	printf("%f", force->force);
	return 0;
}
