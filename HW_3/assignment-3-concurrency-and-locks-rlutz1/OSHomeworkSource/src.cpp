#include "src.hpp"
#include <random>
#include <thread>

std::vector<int> rand_list;
std::atomic<int> rand_idx{0};
int global_n;


// Initialize Queue Methods
void queue_init(queue_t& queue)
{
    node_t* head = (node_t*)malloc(sizeof(node_t));
    head->next = NULL;
    queue.head = head;
    queue.tail = head;
    queue.size = 0;
    queue.initialized = 1234;
}

int queue_empty(queue_t& queue)
{
    return (queue.size == 0);
}

void queue_add(queue_t& queue, pthread_t thread)
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->next = NULL;
    new_node->thread = thread;
    queue.tail->next = new_node;
    queue.tail = new_node;
    queue.size++; 
}

pthread_t queue_remove(queue_t& queue)
{
    node_t* front_thread = queue.head->next;
    queue.head->next = front_thread->next;
    if (front_thread == queue.tail) 
        queue.tail = queue.head;
    queue.size--;
    pthread_t thread = front_thread->thread;
    free(front_thread);
    return thread;
}

void queue_destroy(queue_t& queue)
{
    free(queue.head);
}



// Compute PI Helper
double pthread_compute_pi(int num_threads, int num_samples)
{
    calc_t* pi_calc = (calc_t*)malloc(sizeof(calc_t));
    pi_calc->global_sum = 0;
    pi_calc->global_n_samples = num_samples;
    pi_calc->global_n_threads = num_threads;

    pthread_t* threads = (pthread_t*)malloc(num_threads*sizeof(pthread_t));
    thread_data_t* thread_data = (thread_data_t*)malloc(num_threads*sizeof(thread_data_t));

    init(&(pi_calc->lock));

    for (int i = 0; i < num_threads; i++)
    {
        thread_data[i].pi_calc = pi_calc;
        thread_data[i].thread_id = i;
        pthread_create(&(threads[i]), NULL, compute_pi, &(thread_data[i]));
    }
    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    free(threads);
    free(thread_data);

    destroy(&(pi_calc->lock));
    
    return 4.0 * pi_calc->global_sum / (1.0*num_samples);
}

// Thread Safe Random Value Generator 
void rand_init(int _global_n)
{
}

void rand_destroy()
{
}
thread_local uint64_t state = 88172645463325252ull;
static inline uint64_t xorshift64(uint64_t& x)
{
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}
double thread_rand()
{
    return (xorshift64(state) >> 11) * (1.0 / (1ULL << 53)) * RAND_MAX;
}

double serial_compute_pi(int num_samples, int init_rand)
{
    double rand_x, rand_y;

    // Initializes thread-safe random value generator 
    // Do NOT include this in your compute_pi method

    double global_sum = 0;

    double denom = RAND_MAX*0.5;
    for (int i = 0; i < num_samples; i++)
    {
        rand_x = ((double)(thread_rand()) / denom) - 1;
        rand_y = ((double)(thread_rand()) / denom) - 1;

        if (rand_x*rand_x + rand_y*rand_y <= 1)
            global_sum++;
    }

    // Frees thread-safe random value generator 
    // Do NOT include this in your compute_pi method

    return 4.0 * global_sum / (1.0*num_samples);
    
}
