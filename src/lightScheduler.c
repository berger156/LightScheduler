#include "lightScheduler.h"
#include "TimeService.h"
#include "LightController.h"

#define UNUSED -1

enum {
	TURN_OFF = 0,
	TURN_ON = 1
};

typedef struct {
	int id;
	int minuteOfDay;
	int event;
} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent;

/* static helper functions */
static void scheduleEvent(int id, int day, int minuteOfDay, int event)
{
	scheduledEvent.id = id;
	scheduledEvent.minuteOfDay = minuteOfDay;
	scheduledEvent.event = event;
}

static void operateLight(ScheduledLightEvent *lightEvent)
{
	if(lightEvent->event == TURN_ON) {
		LightController_On(lightEvent->id);
	} else if(lightEvent->event == TURN_OFF) {
		LightController_Off(lightEvent->id);
	}
}

static void processEvent(Time *time, ScheduledLightEvent *lightEvent)
{
	if(lightEvent->id == UNUSED)
	return;
	if(time->minuteOfDay != lightEvent->minuteOfDay)
	return;

	operateLight(lightEvent);
}

void LightScheduler_Create(void)
{
	scheduledEvent.id = UNUSED;
}

void LightScheduler_Destroy(void)
{

}

void LightScheduler_WakeUp(void)
{
	Time time;
	TimeService_GetTime(&time);

	processEvent(&time, &scheduledEvent);
}

void LightScheduler_ScheduleTurnOn(int lightID, int dayOfWeek, int minuteOfDay)
{
	scheduleEvent(lightID, dayOfWeek, minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int lightID, int dayOfWeek, int minuteOfDay)
{
	scheduleEvent(lightID, dayOfWeek, minuteOfDay, TURN_OFF);
}
