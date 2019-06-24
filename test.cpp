#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gnuplot-iostream/gnuplot-iostream.h"
int main ()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    /* using nano-seconds instead of seconds */
    srand((time_t)ts.tv_nsec);

    printf ("Random fast seeded: %d\n", rand()%10);
    return 0;
}