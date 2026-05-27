#include <omp.h>
#include <stdio.h>

/*
Without collapse:
Thread 0: i=0, all j (0,1,2,3)
Thread 1: i=1, all j (0,1,2,3)
Thread 2: i=2, all j (0,1,2,3)
Thread 3: i=3, all j (0,1,2,3)

With collapse(2):
Thread 0: (0,0), (0,1), (1,0), (1,1)
Thread 1: (0,2), (0,3), (1,2), (1,3)
Thread 2: (2,0), (2,1), (3,0), (3,1)
Thread 3: (2,2), (2,3), (3,2), (3,3)
*/

int main() {
    int N = 4;
    int matrix[4][4];
    
    // Collapse nested loops for better parallelization
    #pragma omp parallel for collapse(2)
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            matrix[i][j] = i * N + j;
            printf("Thread %d processes (%d,%d)\n", 
                   omp_get_thread_num(), i, j);
        }
    }
    return 0;
}