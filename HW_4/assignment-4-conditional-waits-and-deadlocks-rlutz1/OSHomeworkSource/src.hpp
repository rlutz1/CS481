#ifndef TEST_SRC_HPP
#define TEST_SRC_HPP

#include <pthread.h>
#include <semaphore.h>
#include "stdlib.h"
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>


// Dining Philosophers
typedef struct __diners_t
{
    sem_t** forks;
    int size;
    pthread_mutex_t mutex;
    int philosopher;
    bool* eat;
} diners_t;

void eat(diners_t* diner);
sem_t* left(diners_t* diner);
sem_t* right(diners_t* diner);

// For you to implement
void* philosopher(void* args);


typedef struct __buffer_t
{
    int limit;
    int* list;
    int put_ctr;
    int get_ctr;
    int size;
    pthread_cond_t empty;
    pthread_cond_t full;
    pthread_mutex_t mutex;
    sem_t* sem_empty;
    sem_t* sem_full;
} buffer_t;

void init(buffer_t* buf, int limit);
void put(buffer_t* buf, int val);
void get(buffer_t* buf, int* val);
void destroy(buffer_t* buf);


typedef struct __data_t
{
    buffer_t* buf;
    int val;
} data_t;

void* producer_thread(void* args);
void* consumer_thread(void* args);


#endif
