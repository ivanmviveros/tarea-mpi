#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


double f(double x)
{
  return pow(x , 3);
}

int main(int argc, char** argv) {
  int i;
  double a = 0.0;
  double b = 10.0;
  double n = 100000.0;
  double suma = 0.0;
  double w = (b-a)/n;
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  
  double x_i;
  if (world_rank == 0) {
    for ( i = 1; i < n; i++)
      {
         x_i = a + i*w;            
         suma = suma + ( f(x_i) ); 
      }
      double total = w*(((f(a)+f(b))/2)+suma);
      printf("Valor aproximado de la integral: %f\n", total);
  } 
  MPI_Finalize();
}