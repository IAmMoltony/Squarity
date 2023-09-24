#include "random.h"
#include <time.h>
#include <stdlib.h>

void RandomInit(void)
{
    srand(time(NULL));
}

int RandomRange(int min, int max)
{
    return rand() % (max + 1 - min) + min;
}
