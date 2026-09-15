#include "src.hpp"
#include "timer.h"

int counter;
void job0(int time)
{
    for (int t = 0; t < time; t++)
        counter += 1;
}

void job1(int time)
{
    for (int t = 0; t < time; t++)
        counter += 1;
}

void job2(int time)
{
    for (int t = 0; t < time; t++)
        counter += 1;
}

void create_jobs(int* n_jobs, Job** jobs)
{
    *n_jobs = 5;
    Job* example_jobs = (Job*)malloc((*n_jobs)*sizeof(Job));

    int priorities[] = {1, 1, 0, 2, 4};
    int indices[] = {2, 0, 1, 3, 4};
    int times[] = {4, 5, 3, 3, 2};
    Operation run_jobs[] = {job0, job1, job2, job0, job1};

    for (int i = 0; i < *n_jobs; i++)
    {
        example_jobs[i].priority = priorities[i];
        example_jobs[i].idx = indices[i];
        example_jobs[i].time = times[i];
        example_jobs[i].run_job = run_jobs[i];
    }

    *jobs = example_jobs;
}




int main(int argc, char* argv[])
{
    int n_jobs;
    Job* jobs;

    // Run Test
    create_jobs(&n_jobs, &jobs);
    counter = 0;

    double t0, tfinal;
    int idx;

    // Find iteration count
    t0 = get_time();
    idx = 0;
    while (get_time() - t0 < 1)
    {
        priority(n_jobs, jobs);
        idx++;
    }

    // Time Priority Scheduler
    t0 = get_time();
    for (int i = 0; i < idx; i++)
        priority(n_jobs, jobs);
    tfinal = (get_time() - t0) / idx;

    printf("Priority Scheduler Takes %e Seconds\n", tfinal);    


    // Find Iteration Count
    t0 = get_time();
    idx = 0;
    while (get_time() - t0 < 1)
    {
        priority_rr(n_jobs, jobs, 3);
        idx++;
    }


    // Time Priority + RR Scheduler
    for (int i = 0; i < idx; i++)
    {  
        priority_rr(n_jobs, jobs, 3);
    }
    tfinal = (get_time() - t0) / idx;

    printf("Priority RR Scheduler Takes %e Seconds\n", tfinal);    
    
    free(jobs);
}
