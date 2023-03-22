#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#include "timer.h"

/* void parallel_alg(long long arrow_of_cycle, long long size_of_chance, int quad_distance, double approximate_p, int thread_count){

  int x,y;
  time_t t;

  srand((unsigned) time(&t));

  #pragma omp parallel for num_threads(thread_count) \
  reduction(+, arrow_of_cycle)

  for(int i=0; i < size_of_chance; i++){
      x = rand() % 2;
      y = rand() % 2;

      quad_distance = x*x + y*y;

      if(quad_distance <= 1)
         arrow_of_cycle++;

  }

  #pragma omp critical

  approximate_p += 4*arrow_of_cycle / (double)size_of_chance;

} */

int main(int argc,char** argv){


   long long size_of_chance = 0;
   long long arrow_of_cycle;
   double x,y,quad_distance;
   long long thread_count = 0;
   double startp,endp,approximate_p_local = 0.0,approximate_p = 0.0;
   time_t t;
   clock_t start,end;

   srand((unsigned) time(&t));

   arrow_of_cycle = 0;
   quad_distance = 0;
   size_of_chance = atoi(argv[1]);
   thread_count = atoi(argv[2]);

   /* serial algorithm */

   startp = omp_get_wtime();

   for(int i=0; i < size_of_chance; i++){
      x = (double)rand() * ( 1 - (-1) ) / (double)RAND_MAX + (-1);
      y = (double)rand() * ( 1 - (-1) ) / (double)RAND_MAX + (-1);

      quad_distance = x*x + y*y;

      if(quad_distance <= 1)
         arrow_of_cycle++;

   }

   /* p number */
   approximate_p = 4*arrow_of_cycle / (double)size_of_chance;

   endp = omp_get_wtime();

   printf("π is %f serial time %.7f \n",approximate_p,endp-startp);

   arrow_of_cycle = 0;
   quad_distance = 0;
   approximate_p = 0.0;

   /* parallel algorithm */

   //parallel_alg(arrow_of_cycle,size_of_chance,quad_distance,approximate_p, thread_count);
   srand((unsigned) time(&t));

   startp = omp_get_wtime();

   #pragma omp parallel for num_threads(thread_count)\
   reduction(+, arrow_of_cycle)

   for(int i=0; i < size_of_chance; i++){
      x = (double)rand() * ( 1 - (-1) ) / (double)RAND_MAX + (-1);
      y = (double)rand() * ( 1 - (-1) ) / (double)RAND_MAX + (-1);

      quad_distance = x*x + y*y;

      if(quad_distance <= 1)
         arrow_of_cycle++;

   }

   /* p number */

   #pragma omp critical

   approximate_p += 4*arrow_of_cycle / (double)size_of_chance;

   endp = omp_get_wtime();

   #pragma omp barrier

   printf("π is %f parallel time %.7f \n",approximate_p,endp-startp);

   return 0;

}
