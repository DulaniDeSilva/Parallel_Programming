#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    #pragma omp parallel for schedule(dynamic, 2)
    for(int i = 0; i < 10; i++) {
        sleep(i % 3); // Simulate varying workload
        printf("Thread %d processes iteration %d\n", 
               omp_get_thread_num(), i);
    }
    return 0;
}