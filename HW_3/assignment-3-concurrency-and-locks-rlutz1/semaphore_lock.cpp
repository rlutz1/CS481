#include "src.hpp"
#include <iostream>

#define _GNU_SOURCE

#define UNLOCKED  0
#define LOCKED    1

void init(lock_t* lock)
{
  lock->S = 1; // init counting semaphore	
  lock->guard = UNLOCKED; // init guard on queue?	
  queue_init(lock->queue); // init a queue again 
}

void my_sig_handler(int signum)
{
}

// equiv to semaphore wait
void lock(lock_t* lock)
{
  // spin for the GUARD lock on the queue
  while (__sync_lock_test_and_set(&(lock->guard), LOCKED) == LOCKED);

   // increment counting semaphore
  __sync_fetch_and_sub(&(lock->S), 1);

  if (lock->S < 0) {
    // the lock has been LOCKED by another thread
    // i need to put my self in the queue and sleep!
    signal(SIGUSR1, my_sig_handler);
    queue_add(lock->queue, pthread_self()); // add myself to queue
    lock->guard = UNLOCKED; // release the guard
    pause(); // go to sleep
  } else { // no one waiting for ressource beyond me
   lock->guard = UNLOCKED;
  } 
}

// equiv to semaphore signal
void unlock(lock_t* lock)
{
  // check if the queue is empty, get the guard first
  while (__sync_lock_test_and_set(&(lock->guard), LOCKED) == LOCKED);

  // add to the semaphore
  __sync_fetch_and_add(&(lock->S), 1);

  if (lock->S <= 0) {
    pthread_t next_thread = queue_remove(lock->queue); // get the next in line
    pthread_kill(next_thread, SIGUSR1); // wake him up!
  }

  lock->guard = UNLOCKED; // release the guard
}

void destroy(lock_t* lock)
{
}
