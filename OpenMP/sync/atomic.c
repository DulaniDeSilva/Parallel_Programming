#include <omp.h>
#include <stdio.h>

// Provides lightweight synchronization for single operations
int main() {
    int counter = 0;
    
    #pragma omp parallel num_threads(4)
    {
        for(int i = 0; i < 1000; i++) {
            #pragma omp atomic
            counter++;
        }
    }
    
    printf("Final counter value: %d\n", counter);
    return 0;
}