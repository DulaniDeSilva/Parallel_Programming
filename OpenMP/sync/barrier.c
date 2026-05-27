#include <omp.h>
#include <stdio.h>
#include <unistd.h>

// Makes threads wait until all threads reach the barrier point

int main() {
    #pragma omp parallel num_threads(4)
    {
        printf("Thread %d starting phase 1\n", omp_get_thread_num());
        sleep(omp_get_thread_num()); // Simulate different work loads
        
        #pragma omp barrier
        
        printf("Thread %d starting phase 2\n", omp_get_thread_num());
    }
    return 0;
}