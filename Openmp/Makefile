omp_monte_carlo: omp_monte_carlo.o
	gcc omp_monte_carlo.o -g -Wall -fopenmp -o omp_monte_carlo
omp_monte_carlo.o: omp_monte_carlo.c
	gcc -c omp_monte_carlo.c
omp_mat_vect_rand_split: omp_mat_vect_rand_split.o
	gcc omp_mat_vect_rand_split.o -g -Wall -fopenmp -o omp_mat_vect_rand_split
omp_mat_vect_rand_split.o: omp_mat_vect_rand_split.c
	gcc -c omp_mat_vect_rand_split.c
clean:
	rm omp_monte_carlo
	rm omp_mat_vect_rand_split
	rm *.o
