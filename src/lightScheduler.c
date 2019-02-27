#include "lightScheduler.h"
#include "TimeService.h"
#include "LightController.h"
#include "RandomMinute.h"
#include "common.h"

#define UNUSED -1
#define MAX_EVENTS 128

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

static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

/* static helper functions */
static int scheduleEvent(int id, int dayOfWeek, int minuteOfDay, int event)
{
	if(id < 0 || id >= MAX_LIGHTS) {
		return LS_ID_OUT_OF_BOUNDS;
	}

	for(int i=0; i<MAX_EVENTS; i++) {
	// search for an UNUSED location to store this event
		if(scheduledEvents[i].id == UNUSED) {
			scheduledEvents[i].id = id;
			scheduledEvents[i].minuteOfDay = minuteOfDay;
			scheduledEvents[i].dayOfWeek = dayOfWeek;
			scheduledEvents[i].event = event;
			return LS_OK;
		}
	}

	return LS_TOO_MANY_EVENTS;
}

static void unscheduleEvent(int id, int dayOfWeek, int minuteOfDay)
{
	for(int i=0; i<MAX_EVENTS; i++) {
		if(scheduledEvents[i].id == id) {
			if(scheduledEvents[i].dayOfWeek == dayOfWeek) {
				if(scheduledEvents[i].minuteOfDay == minuteOfDay) {
					scheduledEvents[i].id = UNUSED;
					break;
				}
			}
		}
	}
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
	for(int i=0; i<MAX_EVENTS; i++) {
		scheduledEvents[i].id = UNUSED;
	}

	TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}

void LightScheduler_Destroy(void)
{
	TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}

void LightScheduler_WakeUp(void)
{
	Time time;
	TimeService_GetTime(&time);

	for(int i=0; i<MAX_EVENTS; i++) {
		processEvent(&time, &scheduledEvents[i]);
	}
}

int LightScheduler_ScheduleTurnOn(int lightID, int dayOfWeek, int minuteOfDay)
{
	return scheduleEvent(lightID, dayOfWeek, minuteOfDay, TURN_ON);
}

int LightScheduler_ScheduleTurnOff(int lightID, int dayOfWeek, int minuteOfDay)
{
	return scheduleEvent(lightID, dayOfWeek, minuteOfDay, TURN_OFF);
}

void LightScheduler_RemoveEvent(int lightID, int dayOfWeek, int minuteOfDay)
{
	unscheduleEvent(lightID, dayOfWeek, minuteOfDay);
}

void LightScheduler_Randomize(int lightID, int dayOfWeek, int minuteOfDay)
{
	for(int i=0; i<MAX_EVENTS; i++) {
		if(scheduledEvents[i].id == lightID) {
			if(scheduledEvents[i].dayOfWeek == dayOfWeek) {
				if(scheduledEvents[i].minuteOfDay == minuteOfDay) {
					scheduledEvents[i].minuteOfDay += RandomMinute_Get();
					break;
				}
			}
		}
	}
}
