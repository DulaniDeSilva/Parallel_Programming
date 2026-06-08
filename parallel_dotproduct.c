#include <stdio.h>
#include <omp.h>

int main(){

    int N = 5;
    float A[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
    float B[5] = {5.0, 4.0, 3.0, 2.0, 1.0};
    float dot = 0.0;

    // reduction (+:dot) accumulate partial sums for each thead
    #pragma omp parallel for reduction(+:dot)
    for(int i=0; i<N; i++){
        dot += A[i] * B[i];
    }

    printf("Dot product = %.1f\n", dot);

    return 0;
}