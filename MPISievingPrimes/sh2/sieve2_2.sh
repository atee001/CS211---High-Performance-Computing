#!/bin/bash
#SBATCH -o sieve2_2.o
#SBATCH -e sieve2_2.err
#SBATCH -J sieve2_2
#SBATCH -N 2
#SBATCH -t 00:10:00

module load mpich-3.2.1
mpirun -np 48 ../main sieve2 10000000000