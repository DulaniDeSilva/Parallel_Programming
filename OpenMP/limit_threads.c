#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{


   #pragma omp parallel num_threads(9)
   {
       printf("Hello World... from therad = %d\n", omp_get_thread_num());
   }

   return 0;
}
