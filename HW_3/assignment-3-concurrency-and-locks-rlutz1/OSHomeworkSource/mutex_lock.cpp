#include "src.hpp"
#include "stdio.h"

void init(lock_t* lock)
{
    pthread_mutex_init(&(lock->mutex), NULL);
}

void lock(lock_t* lock)
{
    pthread_mutex_lock(&(lock->mutex));
}

void unlock(lock_t* lock)
{
    pthread_mutex_unlock(&(lock->mutex));
}

void destroy(lock_t* lock)
{
    pthread_mutex_destroy(&(lock->mutex));
}


