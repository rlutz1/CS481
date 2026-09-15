#include "src.hpp"
#include <math.h>

int main(int argc, char** argv)
{
    double global_sum, serial_global_sum;
    
    int global_n = 1000;
    rand_init(global_n);
    int n_threads;
    for (int iter = 0; iter < 3; iter++)
   {
        serial_global_sum = serial_compute_pi(global_n, 0);
        for (int i = 0; i < 4; i++)
        {
            n_threads = pow(2, i);
            global_sum = pthread_compute_pi(n_threads, global_n);
            if (fabs(serial_global_sum - global_sum) > 0.2)
            {
                printf("Serial pi calculation was %e but your pi calculation was %e\n",
                        serial_global_sum, global_sum);
                return -1;
            }
        }
        
        global_n *= 10;
    }
}
