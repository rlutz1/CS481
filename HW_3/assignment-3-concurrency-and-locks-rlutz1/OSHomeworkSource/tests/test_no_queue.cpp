#include "src.hpp"

lock_t my_lock;
int val;
int finished0, finished1;

int flag0, guard1, flag2, flag3;

void* thread0(void* arg)
{
    lock(&my_lock);
    flag0 = my_lock.flag;
    guard1 = my_lock.guard;
    unlock(&my_lock);

    finished0 = 1;

    return NULL;
}

void* thread1(void* arg)
{
    lock(&my_lock);
    flag2 = my_lock.flag;
    unlock(&my_lock);

    flag3 = my_lock.flag;

    finished1 = 1;

    return NULL;
}

int main(int argc, char** argv)
{
    init(&my_lock);
    if (my_lock.queue.initialized != 1234)
    {
        fprintf(stderr, "Lock is not initialized\n");
        return -1;
    }

    finished0 = 0;
    finished1 = 0;

    pthread_t pthread0;
    pthread_t pthread1;

    // Create thread 0, wait for it to finish
    pthread_create(&pthread0, NULL, thread0, NULL);

    pthread_join(pthread0, NULL);
    if (my_lock.flag != 0)
    {
        fprintf(stderr, "At end of program, flag is %d\n", my_lock.flag);
        return -1;
    }
    if (my_lock.guard != 0)
    {
        fprintf(stderr, "At end of program, guard is %d\n", my_lock.guard);
        return -1;
    }

    // Create thread 1, wait for it to finish
    pthread_create(&pthread1, NULL, thread1, NULL);
    pthread_join(pthread1, NULL);
    if (my_lock.flag != 0)
    {
        fprintf(stderr, "At end of program, flag is %d\n", my_lock.flag);
        return -1;
    }
    if (my_lock.guard != 0)
    {
        fprintf(stderr, "At end of program, guard is %d\n", my_lock.guard);
        return -1;
    }

    if (flag0 != 1)
    {
        fprintf(stderr, "Thread 0 got the lock but flag value was %d\n", flag0);
        return -1;
    }
    if (guard1 != 0) 
    {
        fprintf(stderr, "Thread 0 got the lock but guard value was %d\n", guard1);
        return -1;
    }

    if (flag2 != 1)
    {
        fprintf(stderr, "Thread 1 got the lock but flag value was %d\n", flag2);
        return -1;
    }

    if (flag3 != 0)
    {
        fprintf(stderr, "Thread 1 released lock at end of the program, but flag value was %d\n", flag3);
        return -1;
    }

    destroy(&my_lock);
}
