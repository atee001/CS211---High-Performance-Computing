#!/bin/bash
#SBATCH -o sieve0_1.o
#SBATCH -e sieve0_1.err
#SBATCH -J sieve0_1
#SBATCH -N 1
#SBATCH -t 00:10:00

module load mpich-3.2.1
mpirun -np 24 ../main sieve0 10000000000