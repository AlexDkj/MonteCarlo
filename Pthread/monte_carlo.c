#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

double approximate_p = 0.0;
int iter_start = 0;
int threads_num = 0;

/* thread function of parallel version */
void* thr_func_p(void* arg){

   pthread_mutex_t lock;
   long long arrow_of_cycle;
   int x,y,quad_distance;
   time_t t;

   if(pthread_mutex_init(&lock, NULL) != 0){
        printf("\n mutex init has failed\n");
        pthread_exit(NULL);
   }

   srand((unsigned) time(&t));

   arrow_of_cycle = 0;

   int f = *(int*)arg;

   for(int i = iter_start; i < f; i++){
      x = (double)rand() * ( 1 - (-1) ) / (double)RAND_MAX + (-1);
      y = (double)rand() * ( 1 - (-1) ) / (double)RAND_MAX + (-1);

      quad_distance = x*x + y*y;

      if(quad_distance <= 1)
         arrow_of_cycle++;

   }


   /* only one thread compute and add to approximate_p */

   pthread_mutex_lock(&lock);

   approximate_p += 4*arrow_of_cycle / (double)f;

   pthread_mutex_unlock(&lock);

   pthread_exit(NULL);

}


/* main thread compute serial and parallel versions */
void* thr_func(void* arg){

   long long arrow_of_cycle;
   int x,y,quad_distance = 0;
   long long thread_count = 0;
   time_t t;
   pthread_t pid;
   clock_t start,end;

   srand((unsigned) time(&t));

   arrow_of_cycle = 0;

   /* get from arguments when run the parogram */
   long long f = *(long long*)arg;

   start = clock();

   /* serial version */

   for(int i=0; i < f; i++){
      x = (double)rand() * ( 1 - (-1) ) / (double)RAND_MAX + (-1);
      y = (double)rand() * ( 1 - (-1) ) / (double)RAND_MAX + (-1);

      quad_distance = x*x + y*y;

      if(quad_distance <= 1)
         arrow_of_cycle++;

   }

   approximate_p = 4*arrow_of_cycle / (double)f;

   end = clock();

   printf("π is %f serial time %f \n",approximate_p,((double)end-start)/CLOCKS_PER_SEC);

   approximate_p = 0.0;

   start = clock();

   /* parallel version */

   /* thread chunks */
   thread_count = f / threads_num;

   /* create and join threads */

   for(int i = 0; i < threads_num; ){
      iter_start = i;
      i+=thread_count;
      pthread_create(&pid,NULL,thr_func_p,&thread_count);
      thread_count+=thread_count;
   }

   for(int i = 0; i < threads_num; ){
      i+=thread_count;
      pthread_join(pid,NULL);
   }

   end = clock();

   printf("π is %f parallel time %f \n",approximate_p,((double)end-start)/CLOCKS_PER_SEC);


   pthread_exit(NULL);

}


int main(int argc,char** argv){


   long long number_of_throws = 0;
   pthread_t pid;

   if(argc < 3){
      printf("Usage: ./monte_carlo <number of throws> <thread number> \n");
      return 0;
   }

   number_of_throws = atoi(argv[1]);
   threads_num = atoi(argv[2]);

   /* create main thread */
   pthread_create(&pid,NULL,thr_func,&number_of_throws);

   pthread_join(pid,NULL);

   return 0;

}
