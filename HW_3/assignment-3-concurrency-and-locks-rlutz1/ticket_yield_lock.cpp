#include "src.hpp"

#define _GNU_SOURCE

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

  // instead of spinning, we will yield the CPU
  // until my turn is up
  while (lock->turn != my_turn) {
    sched_yield();
  }

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

