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
  
   // We are assuming at least 2 processes for this task
  if (world_size < 2) {
    fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  double suma_parcial=0;
  double x_j = 0;
  
   if (world_rank == 0) {
    int i;
    
    for (i = 1; i < (world_size); i++){
       MPI_Recv(
        /* data         = */ &suma_parcial, 
        /* count        = */ 1, 
        /* datatype     = */ MPI_DOUBLE, 
        /* source       = */ i, 
        /* tag          = */ 0, 
        /* communicator = */ MPI_COMM_WORLD, 
        /* status       = */ MPI_STATUS_IGNORE);
        suma+=suma_parcial;
    }

    int fraccion = floor(n/world_size);
    int start = world_rank*fraccion;
    int end = (world_rank+1)*fraccion;
    int j;
    if (start==0) start=1;
    for (j = start; j < end; j++) { 
  
        x_j = a + j*w;            
        suma += f(x_j) ;
    } 
    double total = w*(((f(a)+f(b))/2)+suma);
    printf("Valor aproximado de la integral: %f \n",total);
    
  } else {
    int fraccion = floor(n/world_size);
    int start = world_rank*fraccion;
    int end = (world_rank+1)*fraccion;
    int j;
    for (j = start; j < end; j++) { 
        x_j = a + j*w;            
        suma_parcial = suma_parcial + f(x_j);
    } 
   
    MPI_Send(
      /* data         = */ &suma_parcial, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_DOUBLE, 
      /* destination  = */ 0, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD);
   }

  MPI_Finalize();
}