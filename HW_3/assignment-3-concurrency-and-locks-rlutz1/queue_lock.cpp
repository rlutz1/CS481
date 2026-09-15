#include "src.hpp"
#include <iostream>

#define _GNU_SOURCE

#define UNLOCKED 0
#define LOCKED   1

void init(lock_t* lock)
{
  lock->flag = UNLOCKED; // initialize the LOCK lock to unlocked
  lock->guard = UNLOCKED; // initialize the GUARD lock to unlocked
  queue_init(lock->queue); // initalize the queue
}


void my_sig_handler(int signum)
{
}

void lock(lock_t* lock)
{
  // im trying to do some work 
  // spin for the GUARD lock on the queue
  // spin until the lock goes from unlocked to LOCKED!
  while (__sync_lock_test_and_set(&(lock->guard), LOCKED) == LOCKED);

  // this thread has now gotten the guard lock.
  // if the lock is available, lock the lock lock and
  //  unlock the guard.
  if (lock->flag == UNLOCKED) {
    lock->flag = LOCKED; // lock it!
    lock->guard = UNLOCKED; // release the guard
  } else {
    // the lock has been LOCKED by another thread
    // i need to put my self in the queue and sleep!
    signal(SIGUSR1, my_sig_handler);
    queue_add(lock->queue, pthread_self()); // add myself to queue
    lock->guard = UNLOCKED; // release the guard
    pause();		    // go to sleep
  }
  
}

void unlock(lock_t* lock)
{
  // i'm done doing my work, i need to
  // get the guard on queue first
  // i will spin until old state was unlocked and i change to locked!
  while(__sync_lock_test_and_set(&(lock->guard), LOCKED) == LOCKED);
 
  if (!queue_empty(lock->queue)) { // if queue is not empty
  
    pthread_kill(queue_remove(lock->queue), SIGUSR1); // wake next in line up!

  } else {

     lock->flag = UNLOCKED; // unlock the lock lock
  
  }

  lock->guard = UNLOCKED; // unlock the queue
  // leave the lock lock locked for the next thread.

}

void destroy(lock_t* lock)
{

}



