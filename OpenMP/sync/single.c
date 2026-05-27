#include <omp.h>
#include <stdio.h>

// Only one thread (not necessarily master) executes this section
int main() {
    #pragma omp parallel num_threads(4)
    {
        printf("Thread %d is working\n", omp_get_thread_num());
        
        #pragma omp single
        {
            printf("This section is executed by thread %d\n", 
                   omp_get_thread_num());
        }
        // Implicit barrier here
        
        printf("Thread %d continues after single\n", omp_get_thread_num());
    }
    return 0;
}