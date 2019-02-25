#include "lightScheduler.h"
#include "TimeService.h"
#include "LightController.h"
#include "common.h"

#define UNUSED -1

enum {
	TURN_OFF = 0,
	TURN_ON = 1
};

typedef struct {
	int id;
	int minuteOfDay;
	int dayOfWeek;
	int event;
} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent;

/* static helper functions */
static void scheduleEvent(int id, int dayOfWeek, int minuteOfDay, int event)
{
	scheduledEvent.id = id;
	scheduledEvent.minuteOfDay = minuteOfDay;
	scheduledEvent.dayOfWeek = dayOfWeek;
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

static int DoesLightRespondToday(int today, int reactionDay)
{
	if(reactionDay == EVERYDAY)
		return TRUE;
	if(reactionDay == today)
		return TRUE;
	if(reactionDay == WEEKEND && (today == SATURDAY || today == SUNDAY))
		return TRUE;
	if(reactionDay == WEEKDAY && (today >= MONDAY && today <= FRIDAY))
		return TRUE;
	return FALSE;
}

static void processEvent(Time *time, ScheduledLightEvent *lightEvent)
{

	if(lightEvent->id == UNUSED)
	return;
	if(!DoesLightRespondToday(time->dayOfWeek, lightEvent->dayOfWeek))
	return;
	if(time->minuteOfDay != lightEvent->minuteOfDay)
	return;

	operateLight(lightEvent);
}

/* Public API Functions */

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
