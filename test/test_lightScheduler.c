#include "unity.h"
#include "lightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"

void setUp(void)
{
    LightController_Create();
    TimeService_Create();
    LightScheduler_Create();
}

void tearDown(void)
{
    LightScheduler_Destroy();
    LightController_Destroy();
}

/* Tests to verify LightControllerSpy */
void test_NoChangeToLightsDuringInitialization(void)
{
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN,LightControllerSpy_GetLastID());
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN,LightControllerSpy_GetLastState());
}

void test_RememberTheLastLightIDControlled(void)
{
    LightController_On(10);

    TEST_ASSERT_EQUAL(10, LightControllerSpy_GetLastID());
    TEST_ASSERT_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
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
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastID());
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

void test_ScheduleOnEveryday_NotTimeYet(void)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    // schedule light 3 to turn on everyday at 8 pm = 20:00 hrs = 1200 min
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1199);
    LightScheduler_WakeUp();
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastID());
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}
