#ifndef TIMESERVICE_H
#define TIMESERVICE_H

typedef struct Time
{
	int minuteOfDay;
	int dayOfWeek;
} Time;

void TimeService_Create(void);
void TimeService_Destroy(void);
Time TimeService_GetTime(void);

typedef void (*WakeUpCallback)(void);
// a variable type which is a pointer to a function that takes no parameters
// and returns no parameters

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeUpCallback fun);
void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeUpCallback fun);

#endif /* TIMESERVICE_H */
