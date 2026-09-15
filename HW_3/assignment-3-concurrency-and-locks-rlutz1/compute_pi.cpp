#include "src.hpp"
#include <iostream>

void* compute_pi(void* arg)
{
    thread_data_t* data = (thread_data_t*)(arg);
    int thread_id = data->thread_id;
    calc_t* pi_data = data->pi_calc;

    // Task: Update pi_data->global_sum to hold the number of random (x,y) pairs 
    // that fall within the unit circle
    // pi_data->global_n_samples is the total number of (x,y) pairs to be calculated
    // among all threads, combined.
    // Note: you must call thread_rand(), which will give you a thread safe version of rand()
    
    float x, y; // local x, y to use
    int my_samples = pi_data->global_n_samples / pi_data->global_n_threads; // base samples for allthreads
    if (data->thread_id < (pi_data->global_n_samples % pi_data->global_n_threads)) {
      my_samples += 1; // add one to lower level threads only
    }

    int updater = 0; // stack var local to the thread

    // generate samples
    for (int i = 0; i < my_samples; i++) {
      x = thread_rand() / RAND_MAX; // get x
      y = thread_rand() / RAND_MAX; // get y

      // if the sample is within the unit circle
      if ((x * x) + (y * y) <= 1) {
	
	updater++; // use the local counter since unshared by threads

	/*
	// BAD APPROACH, TESTING ONLY!
	lock(&(pi_data->lock));
	pi_data->global_sum = pi_data->global_sum + 1;
	unlock(&(pi_data->lock));
        */
      
      }
    }

    lock(&(pi_data->lock));
    pi_data->global_sum += updater; // update the global sum outside of loop
    unlock(&(pi_data->lock));


   // std::cout << (thread_rand() / RAND_MAX) << std::endl;
   // std::cout << (thread_rand() / RAND_MAX) << std::endl;
    return NULL;
}

