#include "src.hpp"

int main(int argc, char** argv)
{
    lock_t my_lock;

    init(&my_lock);
    if (my_lock.queue.initialized != 1234)
    {
        fprintf(stderr, "Queue lock was not initialized\n");
        return -1;
    }

    if (my_lock.flag != 0)
    {
        fprintf(stderr, "Initial value of flag is %d\n", my_lock.flag);
        return -1;
    }

    if (my_lock.guard != 0)
    {
        fprintf(stderr, "Initial value of guard is %d\n", my_lock.guard);
        return -1;
    }

    if (queue_empty(my_lock.queue) != 1)
    {
        fprintf(stderr, "Initial queue is not empty\n");
        return -1;
    }

    lock(&my_lock);
    if (my_lock.flag != 1)
    {
        fprintf(stderr, "After lock, value of flag is %d\n", my_lock.flag);
        return -1;
    }

    if (my_lock.guard != 0)
    {
        fprintf(stderr, "After lock, value of guard is %d\n", my_lock.guard);
        return -1;
    }
    
    unlock(&my_lock);

    if (my_lock.flag != 0)
    {
        fprintf(stderr, "After unlock, value of flag is %d\n", my_lock.flag);
        return -1;
    }

    if (my_lock.guard != 0)
    {
        fprintf(stderr, "After unlock, value of guard is %d\n", my_lock.guard);
        return -1;
    }
}
