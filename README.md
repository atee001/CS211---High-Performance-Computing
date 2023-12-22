# CS211---High-Performance-Computing Repository
Welcome to the repository for my graduate CS211 High-Performance Computing class. In this repository, you'll find files showcasing C and MPI programming techniques. These programs were executed on an HPC cluster powered by Intel® Xeon® Silver 4214R Processors with 16.5M Cache, 2.40 GHz.

# DgemmOptimized
This directory showcases optimized implementations incorporating techniques such as cache blocking, register blocking, and loop interchanging for the DGEMM (Double precision General Matrix Multiply) operation.

# LUFactorization
This directory contains an implementation of LU Factorization in C, featuring optimized functions for matrix factorization (mydgetrf), forward substitution (mydtrsv for lower triangular matrices), and back substitution (mydtrsv for upper triangular matrices). The LU factorization is performed using partial pivoting.

# MPISievingPrimes
This directory features multiple versions of MPI Sieving Primes, each with optimizations to enhance performance. The optimizations include excluding even numbers from the array of sieving primes, calculating individual sieving primes marked arrays for each processor to eliminate broadcasting, and implementing cache blocking for the sieving primes marked array to minimize cache misses.
