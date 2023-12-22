#!/bin/bash
#SBATCH -o sieve2_3.o
#SBATCH -e sieve2_3.err
#SBATCH -J sieve2_3
#SBATCH -N 3
#SBATCH -t 00:10:00

module load mpich-3.2.1
mpirun -np 72 ../main sieve2 10000000000