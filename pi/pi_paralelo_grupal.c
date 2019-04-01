#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define INTERVALO 20000
#define imprimirvector(V,MA) for (i = 0; i < MA; i++) printf("%d ",V[i]);

int main(int argc, char** argv) {
  int i; 
  double random_x, random_y, distancia_origen, pi=0; 
  int puntos_circulo = 0, puntos_cuadrado = 0; 
  int num_datos_enviados=1;
  int num_datos_recibidos=1;
  int numero_puntos_calcular_proceso;
  int puntos_circulo_parcial;
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


  int numero_puntos_calcular = floor((INTERVALO * INTERVALO)/world_size);
  int puntos_proceso[world_size];
  int numero_puntos_circulo_proceso[world_size];

  //numero de puntos a calcular para cada proceso
  for (i = 0; i < world_size; i++) puntos_proceso[i] = numero_puntos_calcular;

  MPI_Scatter(
    /* sendbuf      = */&puntos_proceso,
    /* sendcount    = */num_datos_enviados,
    /* send datatype= */MPI_INT,
    /* recvbuf      = */&numero_puntos_calcular_proceso,
    /* recvcount    = */num_datos_recibidos,
    /* recv datatype= */MPI_INT,
    /* source       = */ 0,
    /* communicator = */ MPI_COMM_WORLD
    );


  puntos_circulo_parcial = 0;
  for (i = 0; i < numero_puntos_calcular_proceso; i++) { 
  
        random_x = (double) (rand() % (INTERVALO + 1)) / INTERVALO; 
        random_y = (double) (rand() % (INTERVALO + 1)) / INTERVALO; 
        distancia_origen = random_x * random_x + random_y * random_y; 
        
        if (distancia_origen <= 1){
            puntos_circulo_parcial+=1; 
        }
    } 

  MPI_Gather(
    /* sendbuf      = */&puntos_circulo_parcial,
    /* sendbuf    = */num_datos_recibidos,
    /* send datatype= */MPI_INT,
    /* recvbuf      = */&numero_puntos_circulo_proceso,
    /* recvcount    = */num_datos_enviados,
    /* recv datatype= */MPI_INT,
    /* source       = */ 0,
    /* communicator = */ MPI_COMM_WORLD
    );

  if (world_rank==0)
  {
    for (int i = 0; i < world_size; i++)
    {
      puntos_cuadrado += puntos_proceso[i];
      puntos_circulo += numero_puntos_circulo_proceso[i];
    }

    pi = (4.0 * puntos_circulo) / puntos_cuadrado;
    printf("Valor aproximado PI: %f ",pi);   
    printf("\n");
  }
  MPI_Finalize();
}