#include "src.hpp"
#include <stdio.h>
/**
 * ensure you get all locks or no locks
 */
void* philosopher(void* args)
{
    diners_t* diner = (diners_t*)args;
    
    // ensure this philo gets ALL forks or NO forks
    pthread_mutex_lock(&diner->mutex);
    sem_wait(right(diner));
    sem_wait(left(diner));
    pthread_mutex_unlock(&diner->mutex);
 
    eat(diner);
    
    // release forks
    sem_post(right(diner));
    sem_post(left(diner));
    printf("yielding forks\n");

    return NULL; // included due to seg faulting
}
