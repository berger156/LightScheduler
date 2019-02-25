#include "LightControllerSpy.h"

static int lastID;
static int lastState;

/* "Spy" versions of the replaced collaborator "LightController.c"
	Note that no hardware is actually being controlled --------- */
void LightController_Create(void)
{
	lastID = LIGHT_ID_UNKNOWN;
	lastState = LIGHT_STATE_UNKNOWN;
}

void LightController_On(int id)
{
	lastID = id;
	lastState = LIGHT_ON;
}

void LightConroller_Off(int id)
{
	lastID = id;
	lastState = LIGHT_OFF;
}

void LightController_Destroy(void)
{
	// what should this do that isn't handled by Create() on setUp?
}

/* Spy-specific functions */
int LightControllerSpy_GetLastID(void)
{
	return lastID;
}

int LightControllerSpy_GetLastState(void)
{
	return lastState;
}
