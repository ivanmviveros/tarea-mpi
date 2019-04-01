#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  

  int number;
  if (world_rank == 0) {
    for (i = 0; i < (INTERVALO * INTERVALO); i++) { 
  
        random_x = (double) (rand() % (INTERVALO + 1)) / INTERVALO; 
        random_y = (double) (rand() % (INTERVALO + 1)) / INTERVALO; 
        distancia_origen = random_x * random_x + random_y * random_y; 
  
        if (distancia_origen <= 1){
            puntos_circulo++; 
        }
  
        puntos_cuadrado++; 
  
        // estimated pi after this iteration 
        pi = (4.0 * puntos_circulo) / puntos_cuadrado; 
    } 
    printf("Valor aproximado PI: %f ",pi);
  } 
  MPI_Finalize();
}