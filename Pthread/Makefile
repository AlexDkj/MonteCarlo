monte_carlo: monte_carlo.o
	gcc monte_carlo.o -g -Wall -o monte_carlo -lpthread
monte_carlo.o: monte_carlo.c
	gcc -c monte_carlo.c
pth_mat_vect_rand_split: pth_mat_vect_rand_split.o
	 gcc pth_mat_vect_rand_split.o -g -Wall -o pth_mat_vect_rand_split -lpthread
pth_mat_vect_rand_split.o: pth_mat_vect_rand_split.c
	gcc -c pth_mat_vect_rand_split.c
clean:
	rm monte_carlo
	rm *.o
	rm pth_mat_vect_rand_split
