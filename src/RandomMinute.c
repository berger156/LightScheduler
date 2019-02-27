#include "RandomMinute.h"
#include <stdlib.h>

static int Bound = 0;

void RandomMinute_Create(int bound)
{
	Bound = bound;
}

int RandomMinute_Get(void)
{
	return (-Bound + (rand() % (2*Bound + 1)));
}
