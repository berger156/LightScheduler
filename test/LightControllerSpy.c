#include "LightControllerSpy.h"

static int lastID;
static int lastState;

void LightController_Create(void)
{
	lastID = LIGHT_ID_UNKNOWN;
	lastState = LIGHT_STATE_UNKNOWN;
}

int LightControllerSpy_GetLastID(void)
{
	return lastID;
}

int LightControllerSpy_GetLastState(void)
{
	return lastState;
}
