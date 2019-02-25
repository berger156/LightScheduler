#ifndef _LIGHTCONTROLLERSPY_H
#define _LIGHTCONTROLLERSPY_H

#include "LightController.h"

/* literals defined here instead of in LightController.h because they
aren't actually used by LightController.c? */
enum
{
	LIGHT_ID_UNKNOWN = -1,
	LIGHT_STATE_UNKNOWN = -1,
	LIGHT_OFF = 0,
	LIGHT_ON = 1
};

int LightControllerSpy_GetLastID(void);
int LightControllerSpy_GetLastState(void);

#endif // _LIGHTCONTROLLERSPY_H
