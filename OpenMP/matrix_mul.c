// matrix multiplication


#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


#define N 4


int main()
{
 int i, j, k;
 int A[N][N], B[N][N], C[N][N];


 // initialize matrices A and V
 for(i =0; i<N; i++){
   for(j=0; j<N; j++){
     A[i][j] = i+j;
     B[i][j] = i-j;
     C[i][j] = 0; //initialize results matrix C to zero
   }
 }


 // perform matric multiplication in parallel
 #pragma omp parallel for collapse(2) private(i, j, k) shared(A, B, C)
 for(i =0; i<N; i++){
   for(j=0; j<N; j++){
     for(k=0; k<N; k++){
       C[i][j] += A[i][k] * B[k][j];
     }
   }
 }


 printf("Resulting matrix C has been computed \n");
 return 0;
 }




