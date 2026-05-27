#include <omp.h>
#include <stdio.h>

// Global variables private to each thread

int thread_private_var;
#pragma omp threadprivate(thread_private_var)

int main() {
    #pragma omp parallel
    {
        thread_private_var = omp_get_thread_num();
        printf("First parallel region: Thread %d has value %d\n", 
               omp_get_thread_num(), thread_private_var);
    }
    
    #pragma omp parallel
    {
        printf("Second parallel region: Thread %d still has value %d\n", 
               omp_get_thread_num(), thread_private_var);
    }
    return 0;
}
