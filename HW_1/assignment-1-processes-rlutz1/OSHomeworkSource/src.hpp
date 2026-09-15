#ifndef TEST_SRC_HPP
#define TEST_SRC_HPP

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

/***********************************
 * Job Structure
 ***********************************/
typedef void (*Operation)(int t);
typedef struct job
{
    int idx;
    int time;
    int priority;
    Operation run_job;
} Job;


/***********************************
 * To be implemented by you
 **********************************/
// File processes.cpp
void run_processes();
// File scheduler.cpp
void priority(int n_jobs, Job* jobs);
void priority_rr(int n_jobs, Job* jobs, int time_slice);


/***********************************
 * Implemented in each test/example file
 ***********************************/
// For use with processes.cpp
void grandchild();
void child();
void parent();
// For use with scheduler.cpp
void job0(int time);
void job1(int time);
void job2(int time);
void create_jobs(int* n_jobs, Job** jobs);






#endif
