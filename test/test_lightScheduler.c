#include "unity.h"
#include "lightScheduler.h"
#include "mock_LightController.h"
#include "mock_TimeService.h"

void setUp(void)
{
    TimeService_Create();
    LightScheduler_Create();
}

void tearDown(void)
{
    LightScheduler_Destroy();
}

/* helper functions for unit tests */
void setTimeTo(int dayOfWeek, int minuteOfDay)
{
    Time setTime;
    setTime.minuteOfDay = minuteOfDay;
    setTime.dayOfWeek = dayOfWeek;
    TimeService_GetTime_ExpectAndReturn(setTime);
}

/* Tests to verify FakeTimeService */
/*
void test_unsetTime(void)
{
    Time time;  // why is this a local variable?
    TimeService_GetTime(&time);
    TEST_ASSERT_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
}

void test_setTime(void)
{
    Time time;
    FakeTimeService_SetMinute(42);
    FakeTimeService_SetDay(SATURDAY);
    TimeService_GetTime(&time);
    TEST_ASSERT_EQUAL(42, time.minuteOfDay);
    TEST_ASSERT_EQUAL(SATURDAY, time.dayOfWeek);
}
*/

/* Unit Tests for LightScheduler */
void test_NoScheduleNothingHappens(void)
{
    setTimeTo(MONDAY,100);
    LightScheduler_WakeUp();

    /* no expected calls to LightController */
}

void test_ScheduleOnEveryday_NotTimeYet(void)
{
    // schedule light 3 to turn on everyday at 8 pm = 20:00 hrs = 1200 min
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY,1199);

    LightScheduler_WakeUp();

    /* no expected calls to LightController */
}

void test_ScheduleOnEveryday_ItsTime(void)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY,1200);

    LightController_On_Expect(3);

    LightScheduler_WakeUp();
}

void test_ScheduleOffEveryday_ItsTime(void)
{
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    setTimeTo(MONDAY,1200);

    LightController_Off_Expect(3);

    LightScheduler_WakeUp();
}

void test_ScheduleTuesday_ButItsMonday(void)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(MONDAY,1200);

    LightScheduler_WakeUp();
}

void test_ScheduleTuesday_AndItsTuesday(void)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(TUESDAY, 1200);

    LightController_On_Expect(3);

    LightScheduler_WakeUp();
}

void test_ScheduleWeekend_ButItsFriday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(FRIDAY,1200);

    LightScheduler_WakeUp();
}

void test_ScheduleWeekend_AndItsSaturday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SATURDAY,1200);

    LightController_On_Expect(3);

    LightScheduler_WakeUp();
}

void test_ScheduleWeekend_AndItSunday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SUNDAY,1200);

    LightController_On_Expect(3);

    LightScheduler_WakeUp();
}

void test_ScheduleWeekend_ButItsMonday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(MONDAY,1200);

    LightScheduler_WakeUp();
}

void test_ScheduleWeekday_AndItsMonday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(MONDAY,1200);

    LightController_On_Expect(3);

    LightScheduler_WakeUp();
}

void test_ScheduleWeekday_ButItsSunday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(SUNDAY,1200);

    LightScheduler_WakeUp();
}

/*
void test_CreateScheduler_StartsOneMinuteAlarmWithCallback(void)
{
    TEST_ASSERT_EQUAL(60, FakeTimeService_GetAlarmPeriod());
    TEST_ASSERT_EQUAL_PTR(LightScheduler_WakeUp, FakeTimeService_GetAlarmCallback());
}

void test_DestroyScheduler_CancelsOneMinuteAlarm(void)
{
    LightScheduler_Destroy();

    TEST_ASSERT_EQUAL_PTR(NULL, FakeTimeService_GetAlarmCallback());
}
*/
