#include <stdio.h>


__global__ void sumKernel(int *arr, int *result, int N) {
    // Each GPU thread gets a unique index via blockIdx and threadIdx
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) {
        atomicAdd(result, (long long)arr[i]);
    }
}

int main() {
    int N = 10;
    int h_arr[10] = {1,2,3,4,5,6,7,8,9,10}; 
    int h_result = 0;                 

    int *d_arr;           
    int *d_result;  

    // Allocate memory on GPU
    cudaMalloc(&d_arr, N * sizeof(int));
    cudaMalloc(&d_result, sizeof(int));

    // Copy data from CPU to GPU
    cudaMemcpy(d_arr, h_arr, N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_result, &h_result, sizeof(int), cudaMemcpyHostToDevice);

    // Launch kernel: 1 block, 16 threads 
    sumKernel<<<1, 16>>>(d_arr, d_result, N);

    // Copy result back from GPU to CPU
    cudaMemcpy(&h_result, d_result, sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sum = %d\n", h_result);  // Expected: 55

    // Always free GPU memory after use
    cudaFree(d_arr);
    cudaFree(d_result);
    return 0;
}
