#include "unity.h"
#include "lightScheduler.h"
#include "mock_LightController.h"
#include "FakeTimeService.h"

void setUp(void)
{
    TimeService_Create();
    LightScheduler_Create();
}

void tearDown(void)
{
    LightScheduler_Destroy();
}

/* Tests to verify FakeTimeService */
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

/* Unit Tests for LightScheduler */
void test_NoScheduleNothingHappens(void)
{
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(100);
    LightScheduler_WakeUp();

    /* no expected calls to LightController */
}

void test_ScheduleOnEveryday_NotTimeYet(void)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    // schedule light 3 to turn on everyday at 8 pm = 20:00 hrs = 1200 min
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1199);

    LightScheduler_WakeUp();

    /* no expected calls to LightController */
}

void test_ScheduleOnEveryday_ItsTime(void)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    // schedule light 3 to turn on everyday at 8 pm = 20:00 hrs = 1200 min
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);

    LightController_On_Expect(3);

    LightScheduler_WakeUp();
}

void test_ScheduleOffEveryday_ItsTime(void)
{
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    // schedule light 3 to turn on everyday at 8 pm = 20:00 hrs = 1200 min
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);

    LightController_Off_Expect(3);

    LightScheduler_WakeUp();
}
