#!/bin/bash
#SBATCH -o sieve0_5.o
#SBATCH -e sieve0_5.err
#SBATCH -J sieve0_5
#SBATCH -N 5
#SBATCH -t 00:10:00

module load mpich-3.2.1
mpirun -np 120 ../main sieve0 10000000000