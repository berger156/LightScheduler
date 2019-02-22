#ifndef _LIGHTCONTROLLERSPY_H
#define _LIGHTCONTROLLERSPY_H

enum
{
	LIGHT_ID_UNKNOWN = -1,
	LIGHT_STATE_UNKNOWN = -1,
	LIGHT_OFF = 0,
	LIGHT_ON = 1
};

void LightController_Create(void);
int LightControllerSpy_GetLastID(void);
int LightControllerSpy_GetLastState(void);
void LightController_On(int id);

#endif // _LIGHTCONTROLLERSPY_H