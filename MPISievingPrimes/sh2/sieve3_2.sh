#!/bin/bash
#SBATCH -o sieve3_2.o
#SBATCH -e sieve3_2.err
#SBATCH -J sieve3_2
#SBATCH -N 2
#SBATCH -t 00:10:00

module load mpich-3.2.1
mpirun -np 48 ../main sieve3 10000000000