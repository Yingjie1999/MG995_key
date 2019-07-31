//
// Created by song on 19-7-31.
//

#include <MG995_control/utils.h>
#include <cmath>

using namespace std;

int16_t round_float(float number)
{
    return (number > 0.0) ? int16_t(floor(number + 0.5)) : int16_t(ceil(number - 0.5));
}


void mutex_init(lock_t *mutex)
{
    mutex->flag = 0;
}
void lock(lock_t *mutex)
{
    while (TestAndSet(&mutex->flag,1) == 1)
    {
        ;
    }
}
void unlock(lock_t *lock)
{
    lock->flag = 0;
}

int TestAndSet(int *ptr, int n)
{
    int old = *ptr;
    *ptr = n;
    return old;
}

