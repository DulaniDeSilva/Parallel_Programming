#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


# define NUM_STEPS 1000000;


double compute_pi_serial();
double compute_pi_parallel();


int main(){
 double serial_time, parallel_time;
 double pi_serial, pi_parallel;


 serial_time = omp_get_wtime();
 pi_serial = compute_pi_serial();
 serial_time = omp_get_wtime() - serial_time;


 parallel_time = omp_get_wtime();
 pi_parallel = compute_pi_parallel();
 parallel_time = omp_get_wtime() - parallel_time;


 printf("Serial computation of pi: %f\n", pi_serial );
 printf("Time taken for serial computation: %f seconds\n", serial_time);


  printf("Parallel computation of pi: %f\n", pi_parallel);
 printf("Time taken for parallel computation: %f seconds\n", parallel_time);


 return 0;


}


double compute_pi_serial(){
 int i;
 double x, sum = 0.0;
 double step = 1.0/ (double) NUM_STEPS;


  for(i =0; i<NUM_STEPS; i++){
  x =(i+0.5)*step;
  sum += 4.0/ (1.0 + x*x);
}
 return step * sum;
}


double compute_pi_parallel(){
 int i;
 double x, sum = 0.0;
 double step = 1.0/ (double)NUM_STEPS;


 #pragma omp parallel for reduction(+:sum) private(x)
 for(i = 0; i < NUM_STEPS; i++){
   x =(i +0.5)*step;
   sum += 4.0/ (1.0 + x*x);
 }
 return step * sum;
}






