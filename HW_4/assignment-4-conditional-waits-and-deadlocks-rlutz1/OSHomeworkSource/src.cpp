#include "src.hpp"
#include "stdio.h"

void eat(diners_t* diner)
{
    if (sem_trywait(left(diner)) == 0)
    {
        sem_post(left(diner));
        return;
    }

    if (sem_trywait(right(diner)) == 0)
    {
        sem_post(right(diner));
        return;
    }
        
    diner->eat[diner->philosopher] = true;
}

sem_t* left(diners_t* diner)
{
    int pos = diner->philosopher - 1; 
    if (pos < 0)
        pos += diner->size;
    return diner->forks[pos];
}

sem_t* right(diners_t* diner)
{
    return diner->forks[diner->philosopher];
}



void init(buffer_t* buf, int limit)
{
    buf->list = new int[limit];
    buf->limit = limit;
    buf->put_ctr = 0;
    buf->get_ctr = 0;
    buf->size = 0;

    pthread_cond_init(&(buf->full), NULL);
    pthread_cond_init(&(buf->empty), NULL);
    pthread_mutex_init(&(buf->mutex), NULL);

    // If named semaphore already exists
    // delete and unlink it
    buf->sem_empty = sem_open("empty", 0);
    if (buf->sem_empty != SEM_FAILED)
    {
        sem_close(buf->sem_empty);
        sem_unlink("empty");
    }
    buf->sem_full = sem_open("full", 0);
    if (buf->sem_full != SEM_FAILED)
    {
        sem_close(buf->sem_full);
        sem_unlink("full");
    }


    buf->sem_empty = sem_open("empty", O_CREAT, S_IRUSR | S_IWUSR, limit);
    buf->sem_full = sem_open("full", O_CREAT, S_IRUSR | S_IWUSR, 0);
}

void put(buffer_t* buf, int val)
{
    buf->list[buf->put_ctr] = val;
    buf->put_ctr = (buf->put_ctr+1) % buf->limit;
    buf->size++;
}

void get(buffer_t* buf, int* val_ptr)
{
    *val_ptr = buf->list[buf->get_ctr];
    buf->get_ctr = (buf->get_ctr+1) % buf->limit;
    buf->size--;
}

void destroy(buffer_t* buf)
{
    delete[] buf->list;

    pthread_cond_destroy(&(buf->full));
    pthread_cond_destroy(&(buf->empty));
    pthread_mutex_destroy(&(buf->mutex));

    sem_close(buf->sem_empty);
    sem_close(buf->sem_full);
    sem_unlink("empty");
    sem_unlink("full");
}

