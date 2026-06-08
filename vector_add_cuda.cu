#include <stdio.h>
#include <cuda.h>


__global__ void vecAddKernel(float *A, float *B, float *C, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N)
        C[i] = A[i] + B[i];   
}

int main() {
    int N = 6;
    float h_A[6] = {1,2,3,4,5,6};
    float h_B[6] = {6,5,4,3,2,1};
    float h_C[6] = {0};

    float *d_A, *d_B, *d_C;
    int bytes = N * sizeof(float);

    cudaMalloc(&d_A, bytes);
    cudaMalloc(&d_B, bytes);
    cudaMalloc(&d_C, bytes);

    cudaMemcpy(d_A, h_A, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, bytes, cudaMemcpyHostToDevice);

    // Launch with enough threads to cover all N elements
    vecAddKernel<<<1, 32>>>(d_A, d_B, d_C, N);

    cudaMemcpy(h_C, d_C, bytes, cudaMemcpyDeviceToHost);

    printf("Result vector C:\n");
    for (int i = 0; i < N; i++)
        printf("C[%d] = %.1f\n", i, h_C[i]);  

    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    return 0;
}
