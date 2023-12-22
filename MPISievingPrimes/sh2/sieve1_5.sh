#!/bin/bash
#SBATCH -o sieve1_5.o
#SBATCH -e sieve1_5.err
#SBATCH -J sieve1_5
#SBATCH -N 5
#SBATCH -t 00:10:00

module load mpich-3.2.1
mpirun -np 120 ../main sieve1 10000000000