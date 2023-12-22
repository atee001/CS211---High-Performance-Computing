#include <stdint.h>

void dgemm6_jki(double *C,double *A,double *B,int n)
{
    uint16_t j,k,i;
    register double r;

    for(j = 0; j < n; j++){
        for(k = 0; k < n; k++){
            r = B[k*n + j];
            for(i = 0; i < n; i++){
                C[i*n + j] += A[i*n + k] * r;
            }
        }
    }
    
}

void dgemm6_jki2(double *C,double *A,double *B,int n)
{
    uint16_t i, j, k;
    uint16_t i1, j1, k1;
    uint8_t BlockSize = 36;
    register double r;
    printf("jki2 Version\n");
    for (j = 0; j < n; j +=BlockSize){               
        for(k = 0; k < n; k+=BlockSize){
            for(i = 0; i < n; i += BlockSize){ 
                for(j1 = j; j1 < j+BlockSize; j1++){
                    for(k1 = k; k1 < k + BlockSize; k1++){                                            
                        r = B[k1*n + j1];
                        for(i1 = i; i1 < i+BlockSize; i1++){
                            C[i1*n + j1] += A[i1*n + k1] * r; 
                        }                        
                    }
                }
            }
        }
    }
}