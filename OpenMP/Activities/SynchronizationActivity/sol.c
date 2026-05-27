#include <stdio.h>
#include <omp.h>
#define N 1000

int main() {
    int array[N];
    int sum = 0;
    int count = 0;

    for(int i = 0; i < N; ++i) {
        array[i] = 1;
    }

    #pragma omp parallel shared(array, sum, count)
    {
        int local_sum = 0;
        int local_count = 0;
        #pragma omp for
        for(int i = 0; i < N; ++i) {
            local_sum += array[i];
            local_count++;
        }
        #pragma omp critical        // Update to critical
        sum += local_sum;
        count += local_count;     
    }

    printf("Sum: %d, Count: %d\n", sum, count);
    return 0;
}
