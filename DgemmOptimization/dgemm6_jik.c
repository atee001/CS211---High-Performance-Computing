#include <stdint.h>

void dgemm6_jik(double *C,double *A,double *B,int n)
{
    uint16_t i,j,k;
    register double  r;
    for(j = 0; j < n; j++){
        for(i = 0; i < n; i++){
            r = C[i*n + j];
            for(k = 0; k < n; k++){
                r += A[i*n + k] * B[k*n + j];
            }
            C[i*n + j] = r;
        }
    }
    
}

void dgemm6_jik2(double *C,double *A,double *B,int n)
{
    uint16_t i, j, k;
    uint16_t i1, j1, k1;
    uint8_t BlockSize = 36;
    register double r;
    printf("jik2 Version\n");
    for (j = 0; j < n; j +=BlockSize){
        for(i = 0; i < n; i += BlockSize){        
            for(k = 0; k < n; k+=BlockSize){
                for(j1 = j; j1 < j+BlockSize; j1++){
                    for(i1 = i; i1 < i+BlockSize; i1++){                        
                        r = C[i1*n + j1];
                        for(k1 = k; k1 < k + BlockSize; k1++){
                            r += A[i1*n + k1] * B[k1*n + j1]; 
                        }
                        C[i1*n + j1] = r;
                    }
                }
            }
        }
    }
    
}