#include "src.hpp"

int main(int argc, char** argv)
{
    lock_t my_lock;

    init(&my_lock);
    if (my_lock.S != 1)
    {
        fprintf(stderr, "Initial value of S is %d\n", my_lock.S);
        return -1;
    }
    
    lock(&my_lock);
    if (my_lock.S != 0)
    {
        fprintf(stderr, "After lock, value of S is %d\n", my_lock.S);
        return -1;
    }

    unlock(&my_lock);
    if (my_lock.S != 1)
    {
        fprintf(stderr, "After unlock, value of S is %d\n", my_lock.S);
        return -1;
    }

}
