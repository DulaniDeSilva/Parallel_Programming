#include <stdio.h>
#include <omp.h>

int main(){

    float A[6] = {1.0, 2.0, 3.0, 3.0, 5.0, 6.0};
	float B[6] = {6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
	float C[6];

    #pragma omp parallel for
    for(int i=0; i<6; i++){
        C[i] = A[i] + B[i];
        printf("Thread %d: C[%d] = %f\n", omp_get_thread_num(), i, C[i]);
    }

    printf("\nResult Vector C:\n");
    for(int i=0; i<6; i++){
        printf("c[%d] = %.1f\n", i, C[i]);
    }

    return 0;
}