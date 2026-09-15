#include "src.hpp"

int main(int argc, char** argv)
{
    lock_t my_lock;

    init(&my_lock);
    if (my_lock.ticket != 0)
    {
        fprintf(stderr, "Initial value of ticket is %d\n", my_lock.ticket);
        return -1;
    }
    if (my_lock.turn != 0)
    {
        fprintf(stderr, "Initial value of turn is %d\n", my_lock.turn);
        return -1;
    }

    lock(&my_lock);
    if (my_lock.ticket != 1)
    {
        fprintf(stderr, "After lock, value of ticket is %d\n", my_lock.ticket);
        return -1;
    }
    if (my_lock.turn != 0)
    {
        fprintf(stderr, "After lock, value of turn is %d\n", my_lock.turn);
        return -1;
    }
    
    unlock(&my_lock);
    if (my_lock.ticket != 1)
    {
        fprintf(stderr, "After unlock, value of ticket is %d\n", my_lock.ticket);
        return -1;
    }
    if (my_lock.turn != 1)
    {
        fprintf(stderr, "After unlock, value of turn is %d\n", my_lock.turn);
        return -1;
    }
    
}
