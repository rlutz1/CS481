#include "src.hpp"
#include <sys/time.h>

lock_t my_lock;
bool first, timed_out;
bool thread0bool, thread1bool;
bool finished0, finished1;
bool finished;

void timeout_sig_handler(int signum)
{
    timed_out = true;
    unlock(&my_lock);
}

void kill_sig_handler(int signum)
{
    throw "Timed Out";
}

void* thread1(void* arg)
{
    lock(&my_lock);
    thread0bool = first==false;
    first = true;
    unlock(&my_lock);

    finished1 = true;

    return NULL;
}

void* thread0(void* arg)
{
    while (my_lock.S > 0 && !first)
        sched_yield();
    while (my_lock.S <= 0) 
        sched_yield();
    lock(&my_lock);
    thread1bool = first==true;
    unlock(&my_lock);

    finished0 = true;

    return NULL;
}

void* thread_timeout(void* arg)
{
    signal(SIGUSR1, timeout_sig_handler);
    lock(&my_lock);
    lock(&my_lock);

    return NULL;
}

void timer_handler(int signum)
{
    timed_out = true;
}

int main(int argc, char** argv)
{
    init(&my_lock);
    first = false;
    finished = false;
    finished0 = finished1 = false;

    pthread_t pthread0;
    pthread_t pthread1;

    pthread_create(&pthread0, NULL, thread0, NULL);
    pthread_create(&pthread1, NULL, thread1, NULL);
    sleep(1);
    if (!finished0)
        pthread_kill(pthread0, SIGUSR2);
    if (!finished1)
        pthread_kill(pthread1, SIGUSR2);
    pthread_join(pthread0, NULL);
    pthread_join(pthread1, NULL);

    
    if (thread0bool != true)
    {
        fprintf(stderr, "Issue with semaphore lock, value of S was not correct when checked.");
        return -1;
    }  
    if (thread1bool != true)
    {
        fprintf(stderr, "Issue with semaphore lock, value of S was not correct when checked.");
        return -1;
    }  

    destroy(&my_lock);
}
