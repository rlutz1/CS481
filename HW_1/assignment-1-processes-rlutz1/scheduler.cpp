#include "src.hpp"

// constants for sorting consolidation
#define SORT_BY_PRIORITY 'p'
#define SORT_BY_IDX 'i'

// signatures utility methods used
void sort_priority_runs(Job* jobs, int start_idx, int end_idx);
void sort(Job* jobs, int start_idx, int end_idx, char sort_by);
int min (int x, int y);


// Priority Scheduling 
//   -- Jobs with highest priority (lowest number) run first
//   -- If multiple jobs with same priority, lowest index runs first
void priority(int n_jobs, Job* jobs)
{
  // (1) sort jobs by priority (preprocess)
  sort(jobs, 0, n_jobs, SORT_BY_PRIORITY);
  // print_jobs(jobs, n_jobs); // testing
  // (2) sort inner runs with same priority by idx (preprocess)
  sort_priority_runs(jobs, 0, n_jobs);
  // (3) run all jobs
  Job curr_job;
  for (int i = 0; i < n_jobs; i++) {
    curr_job = jobs[i];
    curr_job.run_job(curr_job.time);
  } // end loop

} // end method


// Priority Scheduling with Round Robin 
//    -- Jobs with highest priority (lowest number) run first
//    -- If multiple jobs have same priority, run all in round robin 
//    -- Time slice for round robin passed as a parameter
void priority_rr(int n_jobs, Job* jobs, int time_slice)
{
  // same approach as before to begin:
  // (1) sort by priority, then (2) sort priority runs by fifo order.
  sort(jobs, 0, n_jobs, SORT_BY_PRIORITY);
  sort_priority_runs(jobs, 0, n_jobs);

  // (3) run but with round robin rules
  int i, k, total_time, min_time, run_end;
  Job curr_job, other_job;
  
  for (i = 0; i < n_jobs; i++) { // for every job  
    run_end = i + 1; // next job index
    curr_job = jobs[i]; // current job
     
    if (run_end < n_jobs) { // index check, not at end of list
      other_job = jobs[run_end]; // grab next in line 

      if (other_job.priority == curr_job.priority) { // if we encounter a priority run

        total_time = other_job.time + curr_job.time; // init with at least sum of curr and next job time
        run_end++; // assume that run end is next in iteration
        
        // while we're in a priority run
        while (run_end < n_jobs) {
          other_job = jobs[run_end]; // for ease of use/memory access
	  if (other_job.priority == curr_job.priority) { // if same priority
            total_time += other_job.time; // gather total runtime of the run
            run_end++; // increase the run end marker
	  } else {
            break; // break if out of priority run
	  } // end if
        } // end loop 
      
        // we have now gathered the entire run, now time to run round robin
        while (total_time > 0) { // use total time as a control mech 
          for (k = i; k < run_end; k++) { // iterate through the run
	    curr_job = jobs[k]; // the current job to run round robin
	    if (curr_job.time > 0) { // if still time left on the job
	      min_time = min(curr_job.time, time_slice); // grab the smaller of time left or time slice
	      curr_job.run_job(min_time); // run the job for this amount of time
              total_time -= min_time; // decrement total runtime
	      jobs[k].time -= min_time; // decrement time left for this job 
	    } // end if
	  } // end loop
        } // end loop

        i = run_end - 1; // set up for next iteration

     } else { // if this is NOT a priority run
      curr_job.run_job(curr_job.time); // run as normal
     } // end if

    } else { // last element, just run it
      curr_job.run_job(curr_job.time);
    } // end if
      
  } // end loop
} // end method


// =====================================================
// UTILITY METHODS
// @author Roxanne Krause
// =====================================================

// simple return min of 2 ints method
int min(int x, int y) {
  if (x < y) {
    return x;
  }
  return y;
} // end method


// ease of use method to specific through a constant char
// on what to sort by.
// forgive that this just uses bubble sort, to be clear i
// KNOW that's a bad sort, but its a simple one to use here.
void sort(Job* jobs, int start_idx, int end_idx, char sort_by) {
  int i, j;
  Job temp;

  switch (sort_by) {
    case SORT_BY_PRIORITY:

       for (i = start_idx; i < end_idx; i++) {
         for (j = i + 1; j < end_idx; j++) {
           if (jobs[j].priority < jobs[i].priority) {
             temp = jobs[i];
             jobs[i] = jobs[j];
             jobs[j] = temp;
           } // end if
         } // end loop
       } // end loop
       
       break;

    case SORT_BY_IDX:

      for (i = start_idx; i < end_idx; i++) {
         for (j = i + 1; j < end_idx; j++) {
           if (jobs[j].idx < jobs[i].idx) {
             temp = jobs[i];
             jobs[i] = jobs[j];
             jobs[j] = temp;
           } // end if
         } // end loop
       } // end loop

       break;

    default:
      printf("No idea what to sort by.\n");
  } // end switch

} // end method

// method to sort the jobs by inner "runs",
// meaning runs where the priority is the same.
// we will sort these mini lists by idx to break ties
// via fifo
void sort_priority_runs(Job* jobs, int start_idx, int end_idx) {

  int run_end;
  Job curr_job;

  for (int i = start_idx; i < end_idx; i++) { // for every job
     
    curr_job = jobs[i];
    run_end = i + 1; // next element

    // see where the end of the priority run is
    while (run_end < end_idx && curr_job.priority == jobs[run_end].priority) {
      run_end++;
    } // end loop
    
    sort(jobs, i, run_end, SORT_BY_IDX); // sort the run by index

    i = run_end - 1; // jump the iterator forward

  } // end loop
} // end method



