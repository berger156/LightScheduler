#ifndef TIMESERVICE_H
#define TIMESERVICE_H

typedef struct Time
{
	int minuteOfDay;
	int dayOfWeek;
} Time;

void TimeService_Create(void);
void TimeService_Destroy(void);
void TimeService_GetTime(void);

#endif /* TIMESERVICE_H */
