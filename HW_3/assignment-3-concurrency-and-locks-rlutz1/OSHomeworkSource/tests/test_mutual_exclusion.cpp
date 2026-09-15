#include "src.hpp"

lock_t my_lock;
volatile int value = 0;
int n_loops = 10000;
int* finished;

void queue_sig_handler(int signum)
{
}

void* thread(void* arg)
{
    int* id = (int*)arg;

    lock(&my_lock);
    for (int i = 0; i < n_loops; i++) 
        value++;
    unlock(&my_lock);
    __sync_synchronize();

    finished[*id] = 1;
    return NULL;   
}

int main(int argc, char** argv)
{
    init(&my_lock);

    int n_threads = 10;
    pthread_t* threads = new pthread_t[n_threads];
    int* thread_ids = new int[n_threads];
    finished = new int[n_threads];

    for (int i = 0; i < n_threads; i++)
    {
        finished[i] = 0;
        thread_ids[i] = i;
        pthread_create(&(threads[i]), NULL, thread, &(thread_ids[i]));
    }

    for (int i = 0; i < n_threads; i++)
    {
        while (!finished[i])
        {
            pthread_kill(threads[i], SIGCONT);
            sched_yield();
        }
        pthread_join(threads[i], NULL);
    }

    if (value != n_threads*n_loops)
    {
        fprintf(stderr, "All threads are updating shared variable, which has value %d but should have %d\n", value, n_threads*n_loops);
        return -1;
    }

    destroy(&my_lock);
}
