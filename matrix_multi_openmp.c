#include <stdio.h>
#include <omp.h>

#define N 4

int main(){

    int A[N][N] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    int B[N][N] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    int C[N][N] = {0};
    int i, j, k;

    #pragma omp parallel for collapse(2) private(i, j, k)
    for(i = 0; i<N; i++){
        for(j = 0; j<N; j++){
            for(k = 0; k<N; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("Result Matrix C:\n");
    for(i = 0; i<N; i++){
        for(j = 0; j<N; j++){
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}