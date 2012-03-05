/*
 * states.h
 *
 *  Created on: Mar 31, 2011
 *      Author: King Broos
 */

#ifndef STATES_H_
#define STATES_H_


/**
 * \file states.h
 *
 * \brief Has some defines
 */

#define	STATE_INIT			1
#define STATE_INTRO			STATE_INIT+1
#define	STATE_MAIN			STATE_INTRO+1
#define	STATE_MEASURE		STATE_MAIN+1
#define	STATE_RESULT		STATE_MEASURE+1
#define	STATE_SETTINGS		STATE_RESULT+1
#define STATE_ROUNDSETTINGS STATE_SETTINGS+1
#define STATE_FLATSETTINGS	STATE_ROUNDSETTINGS+1
#define STATE_OVALSETTINGS	STATE_FLATSETTINGS+1
#define STATE_ROUNDEDRECTSETTINGS	STATE_OVALSETTINGS+1


#endif /* STATES_H_ */
