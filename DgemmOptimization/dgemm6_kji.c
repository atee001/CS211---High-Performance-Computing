#include <stdint.h>

void dgemm6_kji(double *C,double *A,double *B,int n)
{
    uint16_t k,j,i;
    register double r;
    for(k = 0; k < n; k++){
        for(j = 0; j < n; j++){
            r = B[k*n + j];
            for(i = 0; i < n; i++){            
                C[i*n + j] += r*A[i*n + k];                
            }
            
        }
    }
    
}

void dgemm6_kji2(double *C,double *A,double *B,int n)
{
    uint16_t i, j, k;
    uint16_t i1, j1, k1;
    uint8_t BlockSize = 36;
    register double r;
    printf("kji2 Version\n");
    for(k = 0; k < n; k+=BlockSize){        
        for (j = 0; j < n; j +=BlockSize){       
            for(i = 0; i < n; i += BlockSize){       
                for(k1 = k; k1 < k + BlockSize; k1++){    
                    for(j1 = j; j1 < j+BlockSize; j1++){                                                                                                   
                        r = B[k1*n + j1];
                        for(i1 = i; i1 < i+BlockSize; i1++){
                            C[i1*n + j1] += r*A[i1*n + k1]; 
                        }                        
                    }
                }
            }
        }
    }
}