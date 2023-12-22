#ifndef __MY_BLOCK_C__
#define __MY_BLOCK_C__

#include "include.h"

void mydgemm(double *A,double *B,int n,int bid,int b)
{
    //TODO
    //Implement a matrix multiplication here following dgemm7 in HW1
    //The first matrix is A[(bid+1)*b:n,bid*b:(bid+1)*b]
    //The second matrix is B[bid*b:(bid+1)*b,(bid+1)*b:n]
    //b is the block size for dgetrf
}

// double randn(){ //returns rand num between -1 and 1
//     return ((double)rand() / RAND_MAX) * 2.0 - 1.0;
// }


int mydgetrf_block(double *A,int *ipiv,int n)
{
    // // int b=1;//MODIFY
    // // double b[n];
    // double tempv[n];
    // // for(int i = 0; i < n; i++) b[i] = randn();
    // // double Abk[n*n];
    // // memcpy(Abk, A, n*n*sizeof(double));
    // // int pvt[n];
    // // for(int i = 0; i < n; i++) pvt[i] = i+1;    

    // int maxind, temps;
    // double max;
    // //TODO

    // for (int i = 0; i < n - 1; i++){        //pivoting
    //     maxind = i; 
    //     max = fabs(A[i*n + i]);
    //     for(int t = i + 1; t < n; t++){
    //         if(fabs(A[t*n + i]) > max){
    //             maxind = t;
    //             max = fabs(A[t*n + i]);
    //         }
    //     }
    //     if(max == 0){
    //         // printf("LUfactorization failed: coefficient matrix is singular\n"); 
    //         return 0;
    //     }
    //     else{
    //         if(maxind != i){
    //             temps = ipiv[i];
    //             ipiv[i] = ipiv[maxind];
    //             ipiv[maxind] = temps;
    //             //swap rows
    //             memcpy(tempv, &A[i*n], n*sizeof(double));
    //             memcpy(&A[i*n], &A[maxind*n], n*sizeof(double));
    //             memcpy(&A[maxind*n], tempv, n*sizeof(double));                
    //         }
    //     }

    //     for(int j = i+1; j < n; j++){
    //         A[j*n + i] = A[j*n + i]/A[i*n + i];
    //         for(int k = i+1; k < n; k++){
    //             A[j*n + k] = A[j*n + k] - (A[j*n + i] * A[i*n + k]);
    //         }
    //     }

    // }
    return 1;
}

void my_block_f(double *A,double *B,int n)
{
    int *ipiv=(int*)malloc(n*sizeof(int));
    for (int i=0;i<n;i++)
        ipiv[i]=i;
    if (mydgetrf_block(A,ipiv,n)==0) 
    {
        printf("LU factoration failed: coefficient matrix is singular.\n");
        return;
    }
    mydtrsv('L',A,B,n,ipiv);
    mydtrsv('U',A,B,n,ipiv);
}

#endif