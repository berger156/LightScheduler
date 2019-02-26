#ifndef FAKETIMESERVICE_H
#define FAKETIMESERVICE_H

#include "TimeService.h"

enum {TIME_UNKNOWN = -1};

void FakeTimeService_SetMinute(int minuteOfDay);
void FakeTimeService_SetDay(int dayOfWeek);
WakeUpCallback FakeTimeService_GetAlarmCallback(void);
int FakeTimeService_GetAlarmPeriod(void);

#endif /* FAKETIMESERVICE_H */
