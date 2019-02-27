#ifndef _LIGHTSCHEDULER_H
#define _LIGHTSCHEDULER_H

typedef enum Day {
	NONE = -1,
	SUNDAY=1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY,
	EVERYDAY = 10, WEEKDAY, WEEKEND
} Day;

enum { LS_OK, LS_TOO_MANY_EVENTS, LS_ID_OUT_OF_BOUNDS };

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
void LightScheduler_WakeUp(void);
int LightScheduler_ScheduleTurnOn(int lightID, int dayOfWeek, int minuteOfDay);
int LightScheduler_ScheduleTurnOff(int lightID, int dayOfWeek, int minuteOfDay);
void LightScheduler_RemoveEvent(int lightID, int dayOfWeek, int minuteOfDay);
void LightScheduler_Randomize(int lightID, int dayOfWeek, int minuteOfDay);

#endif // _LIGHTSCHEDULER_H
