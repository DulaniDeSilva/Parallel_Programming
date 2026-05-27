#include <omp.h>
#include <stdio.h>

#define N 4

int main() {
    int matrix[N][N] = {{0}};
    
    // Each cell depends on left and top neighbors
    for(int wave = 0; wave < 2*N-1; wave++) {
        #pragma omp parallel for
        for(int i = 0; i <= wave; i++) {
            int j = wave - i;
            if(i < N && j < N) {
                // Process cells in diagonal wave pattern
                if(i > 0 && j > 0) {
                    matrix[i][j] = matrix[i-1][j] + matrix[i][j-1];
                }
                printf("Thread %d processes (%d,%d)\n", 
                       omp_get_thread_num(), i, j);
            }
        }
    }
    return 0;
}