#!/bin/bash
#SBATCH -o sieve0_4.o
#SBATCH -e sieve0_4.err
#SBATCH -J sieve0_4
#SBATCH -N 4
#SBATCH -t 00:10:00

module load mpich-3.2.1
mpirun -np 96 ../main sieve0 10000000000