mpicc() { docker run --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp ashael/openmpi mpicc $1 -o $2 -lm; }

mpirun() { docker run --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp -u $(id -u):$(id -g) ashael/openmpi mpirun -np $1 $2; }

time mpirun 1  pi_secuencial
time mpirun 10 pi_paralelo
time mpirun 10 pi_paralelo_grupal

time mpirun 1  integral_secuencial
time mpirun 10 integral_paralelo
time mpirun 10 integral_paralelo_grupal

time mpirun 1  integral_trapecios_secuencial
time mpirun 10 integral_trapecios_paralelo
time mpirun 10 integral_trapecios_paralelo_grupal
