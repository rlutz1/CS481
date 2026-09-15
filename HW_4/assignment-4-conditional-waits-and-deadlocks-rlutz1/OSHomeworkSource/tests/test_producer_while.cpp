#include "src.hpp"
#include "stdio.h"

int main(int argc, char** argv)
{
    buffer_t* buf = (buffer_t*)malloc(sizeof(buffer_t));

    init(buf, 1);

    pthread_t producer, consumer;
    data_t data;

    int init_val = 101;

    data.buf = buf;
    data.val = init_val;
    pthread_create(&producer, NULL, producer_thread, &data);
    pthread_join(producer, NULL);

    data.val++;
    pthread_create(&producer, NULL, producer_thread, &data);

    usleep(100000);

    pthread_mutex_lock(&(buf->mutex));
    pthread_cond_signal(&(buf->full));
    pthread_cond_signal(&(buf->empty));
    pthread_mutex_unlock(&(buf->mutex));

    usleep(100000);

    pthread_create(&consumer, NULL, consumer_thread, buf);

    int* return_val;
    pthread_join(consumer, (void**)&return_val);
    if (*return_val != init_val)
    {
        fprintf(stderr, "Expected return value %d, got %d\n", init_val, *return_val);
        return -1;
    }

    destroy(buf);
    free(buf);
    return 0;
}
