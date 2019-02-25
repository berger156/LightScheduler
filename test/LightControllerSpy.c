#include "LightControllerSpy.h"

static int lastID;
static int lastState;

void LightController_Create(void)
{
	lastID = LIGHT_ID_UNKNOWN;
	lastState = LIGHT_STATE_UNKNOWN;
}

void LightController_Destroy(void)
{
	// what should this do that isn't handled by Create() on setUp?
}

int LightControllerSpy_GetLastID(void)
{
	return lastID;
}

int LightControllerSpy_GetLastState(void)
{
	return lastState;
}

void LightController_On(int id)
{
	lastID = id;
	lastState = LIGHT_ON;
}
