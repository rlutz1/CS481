//#include <semaphore.h>
#include "src.hpp"
#include <stdio.h>
/**
 * break the circular dependency
 */

void* philosopher(void* args)
{
    diners_t* diner = (diners_t*)args;

    if (diner->philosopher == 0) {
      // philosopher 0 always grabs right first.
      sem_wait(right(diner));
      sem_wait(left(diner));
    
      eat(diner);
    
      sem_post(right(diner));
      sem_post(left(diner));

    } else {
      // everyone else: left then right
      sem_wait(left(diner));
      sem_wait(right(diner));
     
      eat(diner);
     
      sem_post(left(diner));
      sem_post(right(diner));
     
    }

    return NULL; // here due to seg faulting
}
