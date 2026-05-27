#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    #pragma omp parallel for schedule(dynamic)
    for(int i = 0; i < 10; i++) {
        // Simulating varying workload
        sleep(i % 3);
        printf("Thread %d processing iteration %d\n", 
               omp_get_thread_num(), i);
    }
    return 0;
}