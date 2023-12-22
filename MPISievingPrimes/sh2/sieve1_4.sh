#!/bin/bash
#SBATCH -o sieve1_4.o
#SBATCH -e sieve1_4.err
#SBATCH -J sieve1_4
#SBATCH -N 4
#SBATCH -t 00:10:00

module load mpich-3.2.1
mpirun -np 96 ../main sieve1 10000000000