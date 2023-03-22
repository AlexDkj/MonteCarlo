# MonteCarlo
Monte-Carlo parallel algorithm in pthread, openmp and mpi

<b>Compile </b> 

pthread      make or make monte_carlo

openmp       make or make omp_monte_carlo

mpi          make or make mpi_monte_carlo

<b>Run </b> 

pthread      ./monte_carlo numer_of_throws number_of_threads

openmp       ./omp_monte_carlo numer_of_throws number_of_threads

mpi          mpiexec -np number_of_processes ./mpi_monte_carlo

or

mpi          mpiexec -f machines -np number_of_processes ./mpi_monte_carlo with

<b> Test </b>

pthread     script_erg1_monte.sh number_of_throws
  
openmp      script_erg2_monte.sh number_of_throws

mpi         script_erg3_monte.sh number_of_throws number_of_processes
  
