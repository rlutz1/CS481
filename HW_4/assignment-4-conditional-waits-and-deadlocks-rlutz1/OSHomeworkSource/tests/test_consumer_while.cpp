#include "src.hpp"
#include "stdio.h"


int main(int argc, char** argv)
{
    buffer_t* buf = (buffer_t*)malloc(sizeof(buffer_t));

    init(buf, 1);

    pthread_t producer, consumer;
    data_t data;

    pthread_create(&consumer, NULL, consumer_thread, buf);

    usleep(100000);

    pthread_mutex_lock(&(buf->mutex));
    pthread_cond_signal(&(buf->full));
    pthread_cond_signal(&(buf->empty));
    pthread_mutex_unlock(&(buf->mutex));

    usleep(100000);

    data.buf = buf;
    data.val = 5;
    pthread_create(&producer, NULL, producer_thread, &data);

    pthread_join(producer, NULL);

    int* return_val;
    pthread_join(consumer, (void**)&return_val);
    printf("return %d\n", *return_val);
    if (*return_val != data.val)
    {
        fprintf(stderr, "Return val was %d, expected %d\n", *return_val, data.val);
        return -1;
    }

    destroy(buf);
    free(buf);

    return 0;
}
