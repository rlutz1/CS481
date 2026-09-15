#include <semaphore.h>
#include "src.hpp"

/**
 * use a semaphore
 */

void* producer_thread(void* args)
{
    data_t* data = (data_t*)args;
    buffer_t* buf = data->buf;
    int val = data->val;
  
    sem_wait(buf->sem_empty); // attempt to take resource for filling 
    pthread_mutex_lock(&buf->mutex); // lock down the critical put
 
    put(buf, val); // add to buffer
    
    pthread_mutex_unlock(&buf->mutex); // release the lock on critical put
    sem_post(buf->sem_full); // add resource to take for taking

    return NULL; // requested return null
}

void* consumer_thread(void* args)
{
    buffer_t* buf = (buffer_t*)args;

    sem_wait(buf->sem_full); // attempt to take resource for filling
    pthread_mutex_lock(&buf->mutex); // lock down the critical get

    int* val = (int*)malloc(sizeof(int));
    get(buf, val); // take from buffer

    pthread_mutex_unlock(&buf->mutex); // release the lock on critical get
    sem_post(buf->sem_empty); // add resource to take for taking
 
    return val; // return the value from get

}
