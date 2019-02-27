#include "unity.h"
#include "RandomMinute.h"
#include <string.h>
#include <stdio.h>

#define BOUND 30

void setUp(void)
{
    RandomMinute_Create(BOUND);
}

void tearDown(void)
{
}


void ASSERT_WITHIN_RANGE(int testVal, int lowerBound, int upperBound)
{
    if(testVal < lowerBound || testVal > upperBound) {
        printf("bad minute value = %d\n", testVal);
        TEST_FAIL();
    }
}


void test_RandomMinute_IsInRange(void)
{
    int minute;
    minute = RandomMinute_Get();
    ASSERT_WITHIN_RANGE(minute, -BOUND, BOUND);
}

void test_RandomMinute_AllValuesPossible(void)
{
    int hitCount[2*BOUND + 1];
    memset(hitCount, 0, sizeof(hitCount));

    int minute;
    int i;
    int maxIter = 300;
    for(i=0; i<maxIter; i++) {
        minute = RandomMinute_Get();
        ASSERT_WITHIN_RANGE(minute, -BOUND, BOUND);
        hitCount[minute + BOUND]++;
    }

    char failMsg[20];
    for(i=0; i<2*BOUND + 1; i++) {
        snprintf(failMsg,sizeof(failMsg),"no hits at min: %d",i-BOUND);
        TEST_ASSERT_MESSAGE(hitCount[i]>0,failMsg);
    }
}
