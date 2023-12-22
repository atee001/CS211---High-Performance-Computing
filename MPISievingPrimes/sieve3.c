#ifndef __SIEVE3_C__
#define __SIEVE3_C__

#define sievePrimesCnt 9591
#define BLOCKSIZE (48 * 48 * 48 * 4)
#define pSize 1000

#include "include.h"

void sieve3(unsigned long long *global_count, unsigned long long n, int pnum, int pid)
{
    unsigned long long odd_n = (n - 1) / 2;
    unsigned long long BLOCK_LOW = pid * (odd_n) / pnum;              // the smallest value handled by this process
    unsigned long long BLOCK_HIGH = ((pid + 1) * (odd_n) / pnum) - 1; // the largest value handled by this process
    unsigned long long size = BLOCK_HIGH - BLOCK_LOW + 1;

    unsigned long long low_value = (2 * BLOCK_LOW) + 3;
    unsigned long long high_value = (2 * BLOCK_HIGH) + 3;

    // number of integers handled by this process
    if (1 + (n - 1) / pnum < (int)sqrt((double)n)) // high_value of process 0 should be larger than floor(sqrt(n))
    {
        if (pid == 0)
            printf("Error: Too many processes.\n");
        MPI_Finalize();
        exit(0);
    }

    char *marked = (char *)malloc(size); // array for marking multiples. 1 means multiple and 0 means prime
    if (marked == NULL)
    {
        printf("Error: Cannot allocate enough memory.\n");
        MPI_Finalize();
        exit(0);
    }

    // if (n != 10000000000)
    //     printf("WARNING: number of sieving primes is predefined for 10^10 only!");
    // uint32_t *sievePrimes = (uint32_t *)malloc(sievePrimesCnt * sizeof(uint32_t));
    uint32_t sievePrimes[sievePrimesCnt];

    memset(marked, 0, size);

    uint16_t spIndex = 0;

    // TODO: find all the sieving Primes from 3.....10^5 and store into sievePrime array

    // for block low = blocklow(pid = 0) to blockhigh(pid = 0)

    unsigned long long index = 0; // index of current prime among all primes (only works for process 0)
    unsigned long long prime = 3; // current prime broadcasted by process 0

    while (prime * prime <= n)
    {
        unsigned long long first; // index of the first multiple among values handled by this process
        sievePrimes[spIndex++] = prime;
        if (prime * prime > 3)
            first = (prime * prime - 3) / 2; // low value should be 3
        else if (3 % prime == 0)
            first = 0;
        else
            first = prime - (((3 + prime) / 2) % prime);
        for (unsigned long long i = first; i*i < n; i += prime)
            marked[i] = 1;
        index++;

        while (marked[index] == 1)
            index++;
        prime = (2 * index) + 3;
    }

  
    memset(marked, 0, size);

    unsigned long long numBlocks = ceil(size / (double)BLOCKSIZE);    

    for (unsigned long long stride = 0; stride < numBlocks; stride++)
    {
        for (unsigned long long p = 0; p < sievePrimesCnt + pSize; p += pSize)
        {
            register unsigned long long offset = stride * BLOCKSIZE;
            // start from p till p+pSize ensure boundary conditions
            
            for (unsigned long long pi = p; (pi < p + pSize) && (pi < sievePrimesCnt); pi++)
            {

                low_value = 2 * (BLOCK_LOW + (offset)) + 3;
                prime = sievePrimes[pi];
                unsigned long long first; // index of the first multiple among values handled by this process

                if (prime * prime > low_value)
                    first = (prime * prime - low_value) / 2 + ((offset));
                else if (low_value % prime == 0)
                    first = ((offset));
                else
                    first = (prime - (((low_value + prime) / 2) % prime)) + ((offset));

                for (unsigned long long i = first; (i < size) && (i < (offset + BLOCKSIZE)); i += prime)
                {
                    marked[i] = 1;
                }
            }
        }
    }

    // }
    unsigned long long count = (pid == 0) ? 1 : 0; // local count of primes
    for (unsigned long long i = 0; i < size; i++)
        if (marked[i] == 0)
            count++;

    MPI_Reduce(&count, global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
}

#endif
