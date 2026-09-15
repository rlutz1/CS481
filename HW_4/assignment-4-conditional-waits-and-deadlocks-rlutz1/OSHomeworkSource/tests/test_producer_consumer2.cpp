#include "src.hpp"
#include "stdio.h"

int main(int argc, char** argv)
{
    buffer_t* buf = (buffer_t*)malloc(sizeof(buffer_t));

    init(buf, 5);

    int n_p = 10;
    int n_c = 10;
    int n = n_p + n_c;
    pthread_t* threads = (pthread_t*)malloc(n*sizeof(pthread_t));
    data_t* data = (data_t*)malloc(n_p*sizeof(data_t));
    for (int i = 0; i < n_p; i++)
    {
        data[i].buf = buf;
        data[i].val = i;
        pthread_create(&(threads[i]), NULL, producer_thread, &(data[i]));
    }
    for (int i = 0; i < n_c; i++)
    {
        pthread_create(&(threads[n_p+i]), NULL, consumer_thread, buf);
    }

    for (int i = 0; i < n_p; i++)
        pthread_join(threads[i], NULL);

    int ctr = 0;
    int val_ctr = 0;
    for (int i = 0; i < n_c; i++)
    {
        int* return_val;
        pthread_join(threads[n_p+i], (void**)&return_val);
        ctr += i;
        val_ctr += *return_val;
        free(return_val);
    }

    if(ctr != val_ctr)
    {
        fprintf(stderr, "Expected sum of all return values to be %d, but got %d\n", ctr, val_ctr);
        return -1;
    }

    destroy(buf);

    free(threads);
    free(data);
    free(buf);

    return 0;
}
