mpicc() { docker run --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp ashael/openmpi mpicc $1 -o $2 -lm; }

mpirun() { docker run --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp -u $(id -u):$(id -g) ashael/openmpi mpirun -np $1 $2; }

mpicc pi/pi_secuencial.c pi_secuencial
mpicc pi/pi_paralelo.c pi_paralelo
mpicc pi/pi_paralelo_grupal.c pi_paralelo_grupal

mpicc integral/integral_secuencial.c integral_secuencial
mpicc integral/integral_paralelo.c integral_paralelo
mpicc integral/integral_paralelo_grupal.c integral_paralelo_grupal

mpicc integral_metodo_trapecios/integral_trapecios_secuencial.c integral_trapecios_secuencial
mpicc integral_metodo_trapecios/integral_trapecios_paralelo.c integral_trapecios_paralelo
mpicc integral_metodo_trapecios/integral_trapecios_paralelo_grupal.c integral_trapecios_paralelo_grupal
