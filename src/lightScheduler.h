#ifndef _LIGHTSCHEDULER_H
#define _LIGHTSCHEDULER_H

typedef enum Day {
	NONE = -1,
	SUNDAY=1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY,
	EVERYDAY = 10, WEEKDAY, WEEKEND
} Day;

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
void LightScheduler_WakeUp(void);
void LightScheduler_ScheduleTurnOn(int lightID, int dayOfWeek, int minuteOfDay);
void LightScheduler_ScheduleTurnOff(int lightID, int dayOfWeek, int minuteOfDay);

#endif // _LIGHTSCHEDULER_H
