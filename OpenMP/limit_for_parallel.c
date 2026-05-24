#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{

   #pragma omp parallel for num_threads(9)
       for(int i=0; i<=6; i++){
           printf("Hello World.. from thread = %d\n", omp_get_thread_num());
       }

   return 0;
}
