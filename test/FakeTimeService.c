#include "FakeTimeService.h"

/* private-scope variables to simulate the protected time variables from
	TimeService.c */
static long int theMinute;
static int theDay;

/* "Faked" versions of "TimeService.c" functions */
void TimeService_Create(void)
{
	theMinute = TIME_UNKNOWN;
	theDay = TIME_UNKNOWN;
}

void TimeService_GetTime(Time *time)
{
	time->minuteOfDay = theMinute;
	time->dayOfWeek = theDay;
}

void FakeTimeService_SetMinute(int minuteOfDay)
{
	theMinute = minuteOfDay;
}

void FakeTimeService_SetDay(int dayOfWeek)
{
	theDay = dayOfWeek;
}
