#include "unity.h"
#include "lightScheduler.h"
#include "LightControllerSpy.h"

void setUp(void)
{
    LightController_Create();
}

void tearDown(void)
{
}

void test_NoChangeToLightsDuringInitialization(void)
{
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN,LightControllerSpy_GetLastID());
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN,LightControllerSpy_GetLastState());
}
