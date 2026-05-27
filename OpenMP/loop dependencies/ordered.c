#include <omp.h>
#include <stdio.h>

int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    #pragma omp parallel for ordered
    for(int i = 1; i < 10; i++) {
        // Each iteration needs the previous result
        #pragma omp ordered
        {
            arr[i] = arr[i] + arr[i-1];
            printf("Thread %d processes index %d: %d\n", 
                   omp_get_thread_num(), i, arr[i]);
        }
    }
    return 0;
}