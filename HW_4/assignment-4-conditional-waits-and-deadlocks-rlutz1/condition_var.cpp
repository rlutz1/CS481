#include "src.hpp"

/**
 * use only condition variables 
 */

void* producer_thread(void* args)
{
    data_t* data = (data_t*)args;
    buffer_t* buf = data->buf;
    int val = data->val;


    pthread_mutex_lock(&buf->mutex); // lock the mutex
    
    while(buf->size == buf->limit) { // while the buffer is full
      pthread_cond_wait(&buf->empty, &buf->mutex); // wait on the empty condish
    }

    put(buf, val); // put, we should have space
    
    pthread_cond_signal(&buf->full); // signal a consumer

    pthread_mutex_unlock(&buf->mutex); // release the mutex

    return NULL; // returning null as requested
}

void* consumer_thread(void* args)
{
    buffer_t* buf = (buffer_t*)args;

    pthread_mutex_lock(&buf->mutex); // lock the mutex

    while(buf->size == 0) { // while the buffer is empty
      pthread_cond_wait(&buf->full, &buf->mutex); // wait on the full condish
    }

    int* val = (int*)malloc(sizeof(int)); // set aside space in crit section
    get(buf, val); // put, we should have space
    
    pthread_cond_signal(&buf->empty); // signal a producer thread

    pthread_mutex_unlock(&buf->mutex); // release the mutex

    return val; // return value?
}
