#include "unity.h"
#include "lightScheduler.h"
#include "mock_LightController.h"
#include "mock_TimeService.h"

Time simulatedClock = {.dayOfWeek = -1, .minuteOfDay = -1};

/* helper functions for unit tests */
static void setTimeTo(int dayOfWeek, int minuteOfDay)
{
    simulatedClock.dayOfWeek = dayOfWeek;
    simulatedClock.minuteOfDay = minuteOfDay;
}

static void getCurrentTime(Time *time, int num_calls)
{
    time->dayOfWeek = simulatedClock.dayOfWeek;
    time->minuteOfDay = simulatedClock.minuteOfDay;
}

void setUp(void)
{
    TimeService_SetPeriodicAlarmInSeconds_Expect(60,LightScheduler_WakeUp);
    LightScheduler_Create();
    // setup TimeService_GetTime to always use getCurrentTime:
    TimeService_GetTime_StubWithCallback(getCurrentTime);
}

void tearDown(void)
{
    TimeService_CancelPeriodicAlarmInSeconds_Expect(60,LightScheduler_WakeUp);
    LightScheduler_Destroy();
}

/* Tests to verify simulatedClock */
void test_unsetTime(void)
{
    Time time;
    TimeService_GetTime(&time);

    // if setTimeTo() has not been called, simulatedClock is uninitialized
    TEST_ASSERT_EQUAL(-1, time.minuteOfDay);
    TEST_ASSERT_EQUAL(-1, time.dayOfWeek);
}


void test_setTime(void)
{
    Time time;
    setTimeTo(SATURDAY,42);
    TimeService_GetTime(&time);
    TEST_ASSERT_EQUAL(42, time.minuteOfDay);
    TEST_ASSERT_EQUAL(SATURDAY, time.dayOfWeek);
}

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

/* Add support for multiple events */
void test_ScheduleTwoEventsAtTheSameTime(void)
{
    LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
    LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);
    setTimeTo(SUNDAY, 1200);

    LightController_On_Expect(3);
    LightController_On_Expect(12);
    /* NOTE: Using LightController_On_Expect is different than using a spy,
    because a spy can monitor the *state* of of the light, which is slightly
    different than "was it turned ON during this test?" */

    LightScheduler_WakeUp();
}
