#!/bin/bash
#SBATCH -o sieve3_4.o
#SBATCH -e sieve3_4.err
#SBATCH -J sieve3_4
#SBATCH -N 4
#SBATCH -t 00:10:00

module load mpich-3.2.1
mpirun -np 96 ../main sieve3 10000000000