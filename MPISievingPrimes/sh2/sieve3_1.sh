#!/bin/bash
#SBATCH -o sieve3_1.o
#SBATCH -e sieve3_1.err
#SBATCH -J sieve3_1
#SBATCH -N 1
#SBATCH -t 00:10:00

module load mpich-3.2.1
mpirun -np 24 ../main sieve3 10000000000