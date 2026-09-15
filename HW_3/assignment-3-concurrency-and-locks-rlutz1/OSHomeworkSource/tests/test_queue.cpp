#include "src.hpp"

lock_t my_lock;
int val;
bool first;
bool finished0, finished1;
int value = 1;
bool unlocked;
bool guard_bool;
bool flag_bool;
bool is_queue_empty;

void queue_sig_handler(int signum)
{
}

void* thread0(void* arg)
{
    lock(&my_lock);

    // Wait for other thread to enter the queue
    while (queue_empty(my_lock.queue))
    {
        if (my_lock.guard > 1 || my_lock.guard < 0)
        {
            guard_bool = false;
            return NULL;
        }
        if (my_lock.flag != 1)
        {
            flag_bool = false;
            return NULL;
        }
        sched_yield();
    }
    
    // Release the lock
    unlock(&my_lock);

    // unlock should remove them from queue
    is_queue_empty = queue_empty(my_lock.queue);

    return NULL;
}

void* thread1(void* arg)
{
    signal(SIGUSR1, queue_sig_handler);
    lock(&my_lock);
    unlock(&my_lock);
    
    finished1 = true;

    return NULL;
}

int main(int argc, char** argv)
{
    init(&my_lock);
    finished0 = finished1 = false;
    flag_bool = true;
    guard_bool = true;
    if (my_lock.queue.initialized != 1234)
    {
        fprintf(stderr, "Queue lock is not initialized\n");
        return -1;
    }

    pthread_t pthread0;
    pthread_t pthread1;

    // Create first thread, which will grab lock and wait for second thread to enter queue
    pthread_create(&pthread0, NULL, thread0, NULL);

    // Spin until first thread has acquired lock
    while (my_lock.flag == 0)
    {
        sched_yield();
    }

    // Create second thread, should enter queue
    pthread_create(&pthread1, NULL, thread1, NULL);

    pthread_join(pthread0, NULL);
    if (flag_bool != true)
    {
        fprintf(stderr, "Thread 0 did not hold onto the flag\n");
        return -1;
    }
    if (guard_bool != true)
    {
        fprintf(stderr, "Thread 0 had invalid guard number\n");
        return -1;

    }
    if (is_queue_empty != true)
    {
        fprintf(stderr, "Thread 0 found item in queue (it was expected to be empty).\n");
        return -1;
    }

    // Possible for pause to cause thread to get stuck
    // This will make sure they wake up
    while (!finished1)
    {
        pthread_kill(pthread1, SIGUSR1);
        sched_yield();
    }
    pthread_join(pthread1, NULL);

    destroy(&my_lock);
}
