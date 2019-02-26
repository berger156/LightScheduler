#include "FakeTimeService.h"
#include "common.h"

/* private-scope variables to simulate the protected time variables from
	TimeService.c */
static long int theMinute;
static int theDay;
static WakeUpCallback callback;
static int period;

/* "Faked" versions of "TimeService.c" functions */
void TimeService_Create(void)
{
	theMinute = TIME_UNKNOWN;
	theDay = TIME_UNKNOWN;
	callback = NULL;
	period = -1;
}

void TimeService_GetTime(Time *time)
{
	time->minuteOfDay = theMinute;
	time->dayOfWeek = theDay;
}

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeUpCallback fun)
{
	callback = fun;
	period = seconds;
}

void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeUpCallback fun)
{
	if(fun == callback && seconds == period) {
		callback = NULL;
		period = -1;
	}
}

/* faking/spying on the clock */
void FakeTimeService_SetMinute(int minuteOfDay)
{
	theMinute = minuteOfDay;
}

void FakeTimeService_SetDay(int dayOfWeek)
{
	theDay = dayOfWeek;
}

WakeUpCallback FakeTimeService_GetAlarmCallback(void)
{
	return callback;
}

int FakeTimeService_GetAlarmPeriod(void)
{
	return period;
}
