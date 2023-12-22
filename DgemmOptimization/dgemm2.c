#include <stdint.h>

void dgemm2(double *C,double *A,double *B,int n)
{
    int i, j, k;
    int stride = 2;

    for(i = 0; i < n; i+=stride){

        for(j = 0; j < n; j+=stride){

            register int t = i*n + j; 
            register int tt = t+n;

            register double C00 = C[t];
            register double C01 = C[t + 1];
            register double C10 = C[tt];
            register double C11 = C[tt+1];      
            // register double C00 = 0;
            // register double C01 = 0;
            // register double C10 = 0;
            // register double C11 = 0;        

            for(k = 0; k < n; k+=stride){

                register int ta = i*n + k;
                register int tta = ta + n;
                register int tb = k*n + j;
                register int ttb = tb + n;

                register double A00 = A[ta];
                register double A01 = A[ta + 1];
                register double A10 = A[tta];
                register double A11 = A[tta + 1];

                register double B00 = B[tb];
                register double B01 = B[tb + 1];
                register double B10 = B[ttb];
                register double B11 = B[ttb + 1];

                C00 += (A00 * B00) + (A01 * B10);
                C01 += (A00 * B01) + (A01 * B11);
                C10 += (A10 * B00) + (A11 * B10);
                C11 += (A10 * B01) + (A11 * B11);

            }

            C[t] = C00;
            C[t + 1] = C01;
            C[tt] = C10;
            C[tt + 1] = C11;
            
        }

    }
}