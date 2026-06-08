#include <stdio.h>
#include <omp.h>

#define N 4

int main(){

    float A[N][N], B[N][N], C[N][N];
    int i, j;

    // Initialize A and B with some values
    for(i =0; i<N; i++){
        for(j=0; j<N; j++){
            A[i][j] = (float)(i +j + 1);
            B[i][j] = (float)(i-j);
        }
    }

    #pragma omp parallel for collapse(2)
    for(i = 0; i<N; i++){
        for(j=0; j<N;j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    printf("Matrix C = A + B:\n");
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf("%.1f ", C[i][j]);
        }
    }


    return 0;
}