#include <stdio.h>
#include <cuda.h>

__global__ void dotKernel(float *A, float *B, float *result, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N)
        atomicAdd(result, A[i] * B[i]);
}

int main() {
    int N = 5;
    float h_A[5] = {1,2,3,4,5};
    float h_B[5] = {5,4,3,2,1};
    float h_result = 0.0f;

    float *d_A, *d_B, *d_result;
    cudaMalloc(&d_A, N * sizeof(float));
    cudaMalloc(&d_B, N * sizeof(float));
    cudaMalloc(&d_result, sizeof(float));

    cudaMemcpy(d_A, h_A, N*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, N*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_result, &h_result, sizeof(float), cudaMemcpyHostToDevice);

    dotKernel<<<1, 16>>>(d_A, d_B, d_result, N);

    cudaMemcpy(&h_result, d_result, sizeof(float), cudaMemcpyDeviceToHost);

    printf("Dot product = %.1f\n", h_result);  

    cudaFree(d_A); cudaFree(d_B); cudaFree(d_result);
    return 0;
}
