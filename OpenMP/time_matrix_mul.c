// matrix multiplication


#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


#define N 4
int A[N][N], B[N][N], C[N][N];


void initialize_matrices(){
 int i, j;
 for(i =0; i<N; i++){
   for(j =0; j<N; j++){
     A[i][j] = i+j;
     B[i][j] = i-j;
     C[i][j] =0;
   }
 }
}


float matMultiplyParallel(){
 int i, j, k;
 double start_time, end_time, execution_time;


 start_time = omp_get_wtime();
 #pragma omp parallel for private(j, k) shared (A, B, C) collapse(2)
 for(i =0; i<N; i++){
   for(j=0; j<N; j++){
     int sum = 0;
     for(k=0; k<N;k++){
       sum += A[i][j] *B[k][j];
     }
     C[i][j] = sum;
   }
 }
 end_time = omp_get_wtime();
 execution_time = end_time - start_time;
 return execution_time;
}


float matMultiplySerial(){
 int i, j, k;
 double start_time, end_time, execution_time;


 start_time = omp_get_wtime();
 for(i =0; i<N; i++){
   for(j=0; j<N; j++){
     int sum =0;
     for(k=0; k<N; k++){
       sum += A[i][k] * B[k][j];
     }
     C[i][j]= sum;
   }
 }
 end_time = omp_get_wtime();
 execution_time = end_time - start_time;
 return execution_time;
}


int main(){
 initialize_matrices();
 float serial_time = matMultiplySerial();
 float parallel_time = matMultiplyParallel();
 printf("Resulting matrix is calculated \n");
 printf("\n Total execution time seqential: %f seconds\n", serial_time);
 printf("Total execution time parallel: %f seconds\n", parallel_time);


 return 0;
}




