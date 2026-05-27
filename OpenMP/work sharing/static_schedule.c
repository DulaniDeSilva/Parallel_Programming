#include <omp.h>
#include <stdio.h>

int main() {
    const int size = 16;
    
    #pragma omp parallel for schedule(static, 2)
    for(int i = 0; i < size; i++) {
        printf("Thread %d processes iteration %d\n", 
               omp_get_thread_num(), i);
    }
    return 0;
}