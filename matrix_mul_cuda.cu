#include <stdio.h>
#include <cuda.h>

#define N 4

// Each GPU thread computes ONE cell C[row][col]
__global__ void matMulKernel(int *A, int *B, int *C, int n) {
    // 2-D thread index mapped from 2-D grid
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < n && col < n) {
        int sum = 0;
        for (int k = 0; k < n; k++)
            // Matrices stored row-major: element [r][c] = r*n + c
            sum += A[row * n + k] * B[k * n + col];
        C[row * n + col] = sum;
    }
}

int main() {
    int h_A[N*N] = {1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16};
    int h_B[N*N] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1}; 
    int h_C[N*N] = {0};

    int *d_A, *d_B, *d_C;
    int bytes = N * N * sizeof(int);

    cudaMalloc(&d_A, bytes);
    cudaMalloc(&d_B, bytes);
    cudaMalloc(&d_C, bytes);

    cudaMemcpy(d_A, h_A, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, bytes, cudaMemcpyHostToDevice);
    cudaMemset(d_C, 0, bytes);   // Zero out result on GPU

    // 2-D grid: each thread handles one cell
    dim3 blockSize(N, N);    // N*N threads per block
    dim3 gridSize(1, 1);     // 1 block (fine for small N)
    matMulKernel<<<gridSize, blockSize>>>(d_A, d_B, d_C, N);

    cudaMemcpy(h_C, d_C, bytes, cudaMemcpyDeviceToHost);

    printf("Result matrix C (A x I = A):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%4d ", h_C[i*N+j]);
        printf("\n");
    }

    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    return 0;
}
