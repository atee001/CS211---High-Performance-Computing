#include <stdint.h>
void dgemm1(double *C,double *A,double *B,int n)
{
    uint16_t i, j, k;

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            register double r = C[i*n + j];
            for(k = 0; k < n; k++){
                r += A[i*n + k] * B[j + k*n];
            }
            C[i*n + j]  = r;
        }

    }
}