#include "unity.h"
#include "lightScheduler.h"
#include "LightControllerSpy.h"
#include "mock_TimeService.h"

Time time;

void setUp(void)
{
    LightController_Create();
}

void tearDown(void)
{
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

/*
void test_NoScheduleNothingHappens(void)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    // schedule light 3 to turn on everyday at 8 pm = 20:00 hrs = 1200 min
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1199);
    LightScheduler_WakeUp();
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastID());
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}
*/
