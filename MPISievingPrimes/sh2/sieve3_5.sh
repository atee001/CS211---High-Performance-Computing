#!/bin/bash
#SBATCH -o sieve3_5.o
#SBATCH -e sieve3_5.err
#SBATCH -J sieve3_5
#SBATCH -N 5
#SBATCH -t 00:10:00

module load mpich-3.2.1
mpirun -np 120 ../main sieve3 10000000000