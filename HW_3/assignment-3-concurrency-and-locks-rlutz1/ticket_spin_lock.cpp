#include "src.hpp"

#define _GNU_SOURCE

// for readability
#define UNLOCKED 0
#define LOCKED 1

void init(lock_t* lock)
{
  // init the turn to 0
  lock->turn = 0;
  // init the ticket to 0
  lock->ticket = 0;
}

void lock(lock_t* lock)
{
  // ticket spin lock simply spins until the 
  // thread's turn comes up.
  
  // first, grab the current ticket, 
  // and increment it to the next for next thread
  int my_turn = __sync_fetch_and_add(&(lock->ticket), 1);

  while (lock->turn != my_turn); // spin here until turn  
}

void unlock(lock_t* lock)
{
  // next thread -> their turn!
  __sync_fetch_and_add(&(lock->turn), 1);  

}

void destroy(lock_t* lock)
{
  // nothing?
}

