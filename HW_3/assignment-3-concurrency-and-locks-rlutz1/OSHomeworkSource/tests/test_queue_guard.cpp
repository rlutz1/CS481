#include "src.hpp"

lock_t my_lock;
int val;
bool first;
volatile bool finished0, finished1;
bool thread0bool, thread1bool;

void* thread0(void* arg)
{
    lock(&my_lock);
    unlock(&my_lock);
    __sync_synchronize();
    finished0 = true;

    return NULL;
}

void* thread1(void* arg)
{
    while (!finished0);

    lock(&my_lock);
    unlock(&my_lock);
    __sync_synchronize();
    finished1 = true;

    return NULL;
}

int main(int argc, char** argv)
{
    init(&my_lock);
    first = false;
    finished0 = finished1 = false;
    if (my_lock.queue.initialized != 1234)
    {
        fprintf(stderr, "Queue lock was not initialized\n");
        return -1;
    }

    pthread_t pthread0;
    pthread_t pthread1;

    pthread_create(&pthread0, NULL, thread0, NULL);
    pthread_create(&pthread1, NULL, thread1, NULL);
    while (!finished0)
    {
        if(my_lock.guard >= 2)
        {
            fprintf(stderr, "Guard is %d\n", my_lock.guard); 
            return -1;
        }
    }
    while (!finished1)
    {
        pthread_kill(pthread1, SIGCONT);
        sched_yield();
    }
    pthread_join(pthread0, NULL);
    pthread_join(pthread1, NULL);

    destroy(&my_lock);
}

