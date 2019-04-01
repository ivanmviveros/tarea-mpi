#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define INTERVALO 20000

int main(int argc, char** argv) {
  int i; 
  double random_x, random_y, distancia_origen, pi; 
  int puntos_circulo = 0, puntos_cuadrado = 0; 
  srand(time(NULL)); 
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
  int number;
  int numero_puntos_calcular;
  numero_puntos_calcular = floor((INTERVALO * INTERVALO)/world_size);
  int puntos_circulo_parcial=0;
  int puntos_circulo_total=0;
  
   if (world_rank == 0) {
    int i;
    for (i = 1; i < (world_size); i++){
      puntos_cuadrado += numero_puntos_calcular;
      MPI_Send(
      /* data         = */ &numero_puntos_calcular, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_INT, 
      /* destination  = */ i, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD);
   }
   for (i = 1; i < (world_size); i++){
     MPI_Recv(
      /* data         = */ &puntos_circulo_parcial, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_INT, 
      /* source       = */ i, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD, 
      /* status       = */ MPI_STATUS_IGNORE);
     puntos_circulo_total+=puntos_circulo_parcial;
    }

    pi = (4.0 * puntos_circulo_total) / puntos_cuadrado;
    printf("Valor aproximado PI: %f ",pi);
    
  } else {
    int i;
    MPI_Recv(
      /* data         = */ &numero_puntos_calcular, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_INT, 
      /* source       = */ 0, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD, 
      /* status       = */ MPI_STATUS_IGNORE);
    for (i = 0; i < numero_puntos_calcular; i++) { 
  
        random_x = (double) (rand() % (INTERVALO + 1)) / INTERVALO; 
        random_y = (double) (rand() % (INTERVALO + 1)) / INTERVALO; 
        distancia_origen = random_x * random_x + random_y * random_y; 
  
        if (distancia_origen <= 1){
            puntos_circulo_parcial++; 
        }
    } 
    MPI_Send(
      /* data         = */ &puntos_circulo_parcial, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_INT, 
      /* destination  = */ 0, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD);
   }

  MPI_Finalize();
}