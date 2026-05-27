#include <omp.h>
#include <stdio.h>

// Ensures only one thread executes the code block at a time
int main() {
    int sum = 0;
    
    #pragma omp parallel num_threads(4)
    {
        int local_sum = 0;
        for(int i = 0; i < 1000; i++) {
            local_sum++;
        }
        
        #pragma omp critical
        {
            sum += local_sum;
            printf("Thread %d added its local sum\n", omp_get_thread_num());
        }
    }
    
    printf("Final sum: %d\n", sum);
    return 0;
}