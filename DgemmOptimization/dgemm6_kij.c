#include <stdint.h>


void dgemm6_kij(double *C,double *A,double *B,int n)
{
    uint16_t k,i,j;
    register double r;
    for(k = 0; k < n; k++){
        for(i = 0; i < n; i++){
            r = A[i*n + k];
            for(j = 0; j < n; j++){
                C[i*n + j] += r*B[k*n + j];                
            }
        }
    }
    
}

void dgemm6_kij2(double *C,double *A,double *B,int n)
{
    uint16_t i, j, k;
    uint16_t i1, j1, k1;
    uint8_t BlockSize = 36;
    register double r;
    printf("kij2 Version\n");
    for(k = 0; k < n; k+=BlockSize){
        for(i = 0; i < n; i += BlockSize){ 
            for (j = 0; j < n; j +=BlockSize){             
                for(k1 = k; k1 < k + BlockSize; k1++){     
                    for(i1 = i; i1 < i+BlockSize; i1++){                                                                              
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