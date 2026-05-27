#include <omp.h>
#include <stdio.h>

// Only the master thread executes this section
int main() {
    #pragma omp parallel num_threads(4)
    {
        // All threads execute this
        printf("Thread %d is working\n", omp_get_thread_num());
        
        #pragma omp master
        {
            printf("This is only executed by master thread (%d)\n", 
                   omp_get_thread_num());
        }
        
        // No implicit barrier after master
        printf("Thread %d continues\n", omp_get_thread_num());
    }
    return 0;
}