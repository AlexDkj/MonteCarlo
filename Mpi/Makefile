mpi_monte_carlo: mpi_monte_carlo.o
	mpicc -g -Wall mpi_monte_carlo.o -o mpi_monte_carlo
mpi_monte_carlo.o: mpi_monte_carlo.c
	mpicc -g -Wall -c mpi_monte_carlo.c
mpi_mat_vect_time: mpi_mat_vect_time.o
	mpicc -g -Wall mpi_mat_vect_time.o -o mpi_mat_vect_time
mpi_mat_vect_time.o: mpi_mat_vect_time.c
	mpicc -g -Wall -c mpi_mat_vect_time.c
clean:
	rm mpi_monte_carlo
	rm mpi_mat_vect_time
	rm *.o
