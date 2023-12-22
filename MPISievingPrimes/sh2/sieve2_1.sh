#!/bin/bash
#SBATCH -o sieve2_1.o
#SBATCH -e sieve2_1.err
#SBATCH -J sieve2_1
#SBATCH -N 1
#SBATCH -t 00:10:00

module load mpich-3.2.1
mpirun -np 24 ../main sieve2 10000000000