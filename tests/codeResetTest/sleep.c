#include "sleep.h"

#ifdef TESTING_ON_PC
#include <unistd.h>

void sleep_ms(int ms) 
{
    usleep(ms * 1000);
}
#endif
