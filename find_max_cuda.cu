#include <stdio.h>
#include <cuda.h>


__global__ void maxKernel(int *arr, int *result, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N)
        atomicMax(result, arr[i]);  
}

int main() {
    int N = 8;
    int h_arr[8] = {3, 1, 4, 1, 5, 9, 2, 6};
    int h_result = h_arr[0];  // Initialise with first element

    int *d_arr, *d_result;
    cudaMalloc(&d_arr,    N * sizeof(int));
    cudaMalloc(&d_result, sizeof(int));

    cudaMemcpy(d_arr,    h_arr,     N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_result, &h_result, sizeof(int),     cudaMemcpyHostToDevice);

    maxKernel<<<1, 16>>>(d_arr, d_result, N);

    cudaMemcpy(&h_result, d_result, sizeof(int), cudaMemcpyDeviceToHost);

    printf("Maximum value = %d\n", h_result);  // Expected: 9

    cudaFree(d_arr);
    cudaFree(d_result);
    return 0;
}
