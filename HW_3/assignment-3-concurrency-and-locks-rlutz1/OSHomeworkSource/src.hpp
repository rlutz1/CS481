#ifndef TEST_SRC_HPP
#define TEST_SRC_HPP

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <queue>
#include <signal.h>
#include <atomic>

#define rand() thread_rand()

extern std::vector<int> rand_list;
extern std::atomic<int> rand_idx;

// Queue Struct
typedef struct __node_t
{
    struct __node_t* next;
    pthread_t thread;
} node_t;

typedef struct __queue_t
{
    node_t* head;
    node_t* tail;
    int size;
    int initialized;
} queue_t;

void queue_init(queue_t& queue);
int queue_empty(queue_t& queue);
void queue_add(queue_t& queue, pthread_t thread);
pthread_t queue_remove(queue_t& queue);

// Lock Struct
typedef struct __lock_t
{
    // Needed for ticket locks
    volatile int ticket;
    volatile int turn;

    // Needed for semaphore lock
    volatile int S;
    pthread_mutex_t mutex; 

    // Needed for queue lock
    volatile int flag;
    volatile int guard;
    queue_t queue;
} lock_t;

void init(lock_t* lock);
void lock(lock_t* lock);
void unlock(lock_t* lock);
void destroy(lock_t* lock);



// Compute PI
typedef struct __calc_t
{
    int global_sum;
    int global_n_samples;
    int global_n_threads;
    lock_t lock;
} calc_t;

typedef struct __thread_data_t
{
    calc_t* pi_calc;
    int thread_id;
} thread_data_t;

void* compute_pi(void* arg);

double pthread_compute_pi(int num_threads, int num_samples);
double serial_compute_pi(int num_samples, int init_rand = 1);


// Thread Safe Random Value Generator 
void rand_init(int global_n);
void rand_destroy();
double thread_rand();

#endif
