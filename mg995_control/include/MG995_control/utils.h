#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>
#include <unistd.h> //  close
#include <string.h> //  strerror

typedef struct _lock_t { int flag; } lock_t;
int16_t round_float(float number);
void mutex_init(lock_t *mutex);
void lock(lock_t *mutex);
void unlock(lock_t *lock);
int TestAndSet(int *ptr, int n);
#endif
