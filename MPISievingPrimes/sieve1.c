#ifndef __SIEVE1_C__
#define __SIEVE1_C__

#include "include.h"

void sieve1(unsigned long long *global_count,unsigned long long n,int pnum,int pid)
{
    // double tic, toc, total;
    // total = 0;
    unsigned long long odd_n = (n-1)/2;
    
    unsigned long long BLOCK_LOW= pid*(odd_n)/pnum;//the smallest value handled by this process
    unsigned long long BLOCK_HIGH=((pid+1)*(odd_n)/pnum) - 1;//the largest value handled by this process
    unsigned long long size=BLOCK_HIGH-BLOCK_LOW+1;

    unsigned long long low_value = (2*BLOCK_LOW) + 3;    
    unsigned long long high_value = (2*BLOCK_HIGH) + 3;

    //number of integers handled by this process
    if (1+(n-1)/pnum<(int)sqrt((double)n))//high_value of process 0 should be larger than floor(sqrt(n))
    {
        if (pid==0)
            printf("Error: Too many processes.\n");
        MPI_Finalize();
        exit(0);
    }

    char *marked=(char*)malloc(size);//array for marking multiples. 1 means multiple and 0 means prime
    if (marked==NULL)
    {
        printf("Error: Cannot allocate enough memory.\n");
        MPI_Finalize();
        exit(0);
    }
    memset(marked,0,size);

    unsigned long long index=0;//index of current prime among all primes (only works for process 0)
    unsigned long long prime=3;//current prime broadcasted by process 0
    
    do{
        unsigned long long first;//index of the first multiple among values handled by this process

        if (prime*prime>low_value)
            first=(prime*prime-low_value)/2;
        else
            if (low_value%prime==0)
                first=0;
            else 
                first=prime- (((low_value + prime)/2)%prime);
        for (unsigned long long i=first;i<size;i+=prime)
            marked[i]=1;
        index++;
        if (pid==0)
        {
            while (marked[index]==1)
                index++;
            prime=(2*index) + 3;
        }

        MPI_Bcast(&prime,1,MPI_INT,0,MPI_COMM_WORLD);

        // total += (toc - tic);
    } while (prime*prime<=n);

    // if(pid == 0) printf("Number of sieving primes = %d", cnt);
    
    unsigned long long count = (pid == 0) ? 1 : 0;//local count of primes

    for (unsigned long long i=0;i<size;i++)
        if (marked[i]==0)
            count++;

    // if(pid == 0) printf("Total number of sieiving primes (not including 2): %i/n", numSP);
    MPI_Reduce(&count,global_count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

}

#endif