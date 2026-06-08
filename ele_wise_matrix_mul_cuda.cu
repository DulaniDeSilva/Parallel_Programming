#include <stdio.h>
#include <cuda.h>

#define N 5

__global__ void matAddKernel(float *A, float *B, float *C, int n) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < n && col < n)
        C[row * n + col] = A[row * n + col] + B[row * n + col];
}

int main() {
    float h_A[N*N], h_B[N*N], h_C[N*N];
    int bytes = N * N * sizeof(float);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            h_A[i*N+j] = (float)(i + j + 1);
            h_B[i*N+j] = (float)(i - j);
        }

    float *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, bytes);
    cudaMalloc(&d_B, bytes);
    cudaMalloc(&d_C, bytes);

    cudaMemcpy(d_A, h_A, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, bytes, cudaMemcpyHostToDevice);

    dim3 blockSize(N, N);
    dim3 gridSize(1, 1);
    matAddKernel<<<gridSize, blockSize>>>(d_A, d_B, d_C, N);

    cudaMemcpy(h_C, d_C, bytes, cudaMemcpyDeviceToHost);

    printf("Matrix C = A + B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%6.1f ", h_C[i*N+j]);
        printf("\n");
    }

    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    return 0;
}
