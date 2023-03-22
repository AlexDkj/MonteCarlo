#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mpi.h>

long long monte_carlo(long long starti, long long endi){

   long long arrow_of_cycle;
   double x,y,quad_distance;
   //double approximate_p = 0.0;
   time_t t;

   srand((unsigned) time(&t));

   arrow_of_cycle = 0;
   quad_distance = 0;

   for(int i=starti; i < endi; i++){
      x = (double)rand() * ( 1 - (-1) ) / (double)RAND_MAX + (-1);
      y = (double)rand() * ( 1 - (-1) ) / (double)RAND_MAX + (-1);

      quad_distance = x*x + y*y;

      if(quad_distance <= 1)
         arrow_of_cycle++;

   }

   return arrow_of_cycle;

}

int main(void){

   int comm_sz; /* Number of processes    */
   int my_rank; /* My process rank        */
   long long startiter,enditer; /* Number of start and end iteration */
   long long pec; /* Chunks for processes */
   double start,end,approximate_p = 0.0;
   long long aoc,aoc_sum; /* aoc:Arrow of cycle */
   long long numofiter;

   /* Start up MPI */
   MPI_Init(NULL, NULL);

   /* Get the number of processes */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   /* Get my rank among all the processes */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   if(my_rank == 0){
      printf("Give number of iterations: ");
      scanf("%lld",&numofiter);
      printf("\n");
   }

   MPI_Bcast(&numofiter,1,MPI_LONG_LONG_INT,0,MPI_COMM_WORLD);

   /* serial version */

   if(my_rank == 0){

      start = MPI_Wtime();

      aoc = monte_carlo(0,numofiter);

      approximate_p = 4*aoc / (double)numofiter;

      end = MPI_Wtime();

      printf("p is %.7f serial time is %.7f \n",approximate_p,end-start);

      approximate_p = 0.0;
      aoc = 0;
   }

   pec = numofiter / comm_sz;

   /* parallel version */

   if(my_rank == 0)
      start = MPI_Wtime();

   startiter = my_rank * pec;
   enditer = startiter + pec;

   aoc = monte_carlo(startiter,enditer);

   MPI_Reduce(&aoc,&aoc_sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

   MPI_Barrier(MPI_COMM_WORLD);

   if(my_rank == 0){
      approximate_p = 4*aoc_sum / (double)numofiter;
      end = MPI_Wtime();
      printf("p is %.7f parallel time is %.7f \n",approximate_p,end-start);
   }

   MPI_Finalize();

   return 0;

}
