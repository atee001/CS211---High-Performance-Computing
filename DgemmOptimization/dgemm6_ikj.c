#include <stdint.h>

void dgemm6_ikj(double *C,double *A,double *B,int n)
{
    uint16_t i, j, k;

    for(i = 0; i < n; i++){
        for(k = 0; k < n; k++){
            register double r = A[i*n + k];
            for(j = 0; j < n; j++){
                C[i*n + j] += r * B[j + k*n];
            }
        }

    }
    
}

void dgemm6_ikj2(double *C,double *A,double *B,int n)
{
    uint16_t i, j, k;
    uint16_t i1, j1, k1;
    uint8_t BlockSize = 36;
    register double r;
    printf("ikj2 Version\n");
    for(i = 0; i < n; i += BlockSize){        
        for(k = 0; k < n; k+=BlockSize){
            for (j = 0; j < n; j +=BlockSize){
                for(i1 = i; i1 < i+BlockSize; i1++){
                    for(k1 = k; k1 < k + BlockSize; k1++){                    
                        r = A[i1*n + k1];
                        for(j1 = j; j1 < j+BlockSize; j1++){
                            C[i1*n + j1] += r * B[k1*n + j1]; 
                        }                       
                    }
                }
        }
        }
    }
}