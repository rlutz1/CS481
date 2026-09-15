#include "src.hpp"

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

int main(int argc, char** argv)
{
    for (int i = 0; i < 1; i++)
    {
        int n_jobs;
        Job* jobs;

        // Run Test
        create_jobs(&n_jobs, &jobs);
        counter = 0;
        priority(n_jobs, jobs);
        if (counter != 17)
        {
            fprintf(stderr, "Priority scheduler (FIFO) is trying to run with %d jobs, but is running in an incorrect order.  Job information is as follows\n", n_jobs);
            for (int j = 0; j < n_jobs; j++)
                fprintf(stderr, "Job %d has priority %d, idx %d, and time %d\n", j, jobs[j].priority, jobs[j].idx, jobs[j].time);
            free(jobs);
            return 1;
        }
        free(jobs);
    }
    return 0;
}


