#include <omp.h>
#include <stdio.h>

void process_item(int i) {
    printf("Task %d processed by thread %d\n", i, omp_get_thread_num());
}

int main() {
    #pragma omp parallel
    {
        #pragma omp single // Only one thread creates tasks
        {
            for(int i = 0; i < 5; i++) {
                #pragma omp task
                process_item(i);
            }
        }
    }
    return 0;
}