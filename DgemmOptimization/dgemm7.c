#include <stdint.h>
#define CacheBlock 36
#define RBR 2
#define RBC 3

void dgemm7(double *C, double *A, double *B, int n)
{
    uint16_t i, j, k;
    uint16_t i1, j1, k1;

    register double C00, C01, C02, C10, C11, C12;
    register double B00, B10, B20, B01, B11, B21;
    register double A00, A10, A11, A20, A21, A22;
    // register double A00, A10, A20, A30;
    // register double A00, A10;
    register int t, tt, ttt, tttt, ta, tta, ttta, tttta, tb, ttb, tttb, ttttb;

    printf("Register Blocking + Cache Blocking\n");
    for (i = 0; i < n; i += CacheBlock)
    {
        for (j = 0; j < n; j += CacheBlock)
        {
            for (k = 0; k < n; k += CacheBlock)
            {
                for (i1 = i; i1 < i + CacheBlock; i1 += RBR)
                {
                    for (j1 = j; j1 < j + CacheBlock; j1 += RBC)
                    {
                        t = i1*n + j1; 
                        tt = t+n;

                        C00 = C[t];
                        C01 = C[t + 1];
                        C02 = C[t + 2];
                        C10 = C[tt];
                        C11 = C[tt + 1];
                        C12 = C[tt + 2];  

                        for (k1 = k; k1 < k + CacheBlock; k1 += RBC)
                        {

                            ta = i1*n + k1;
                            tta = ta + n;
                            // ttta = tta + n;
                            tb = k1*n + j1;
                            ttb = tb + n;
                            tttb = ttb + n;     

                            A00 = A[ta];
                            A01 = A[ta + 1];
                            A02 = A[ta + 2];
                            A10 = A[tta];
                            A11 = A[tta + 1];
                            A12 = A[tta + 2];


                            B00 = B[tb];
                            B01 = B[tb + 1]; 
                            B10 = B[ttb];
                            B11 = B[ttb + 1];
                            B20 = B[tttb];
                            B21 = B[tttb + 1];

                            C00 += A00*B00 + A01*B10;
                            C01 += A00*B01 + A01*B11;
                            C02 += A00*B02 + A01*B22;

                            C10 += A10*B00 + A11*B10;
                            C11 += A10*B01;
                            C12 += A10*B02;

                            
                                                    

                            // A00 = A[ta];
                            // A10 = A[tta];
                            // A20 = A[ttta];

                            // B00 = B[tb];
                            // B01 = B[tb + 1];
                            // B02 = B[tb + 2];

                            // C00 += A00*B00;
                            // C01 += A00*B01;
                            // C02 += A00*B02;

                            // C10 += A10*B00;
                            // C11 += A10*B01;
                            // C12 += A10*B02;

                            // C20 += A20*B00;
                            // C21 += A20*B01;
                            // C22 += A20*B02;                           

                            // // LD A00 <- A01
                            // // LD A10 <- A11
                            // // LD A20 <- A21

                            // // LD B00 <- B10
                            // // LD B01 <- B11
                            // // LD B11 <- B12

                            // A00 = A[ta + 1]; //A01
                            // A10 = A[tta + 1]; //A11
                            // A20 = A[ttta + 1]; //A21

                            // B00 = B[ttb]; //B10
                            // B01 = B[ttb + 1]; //B11
                            // B02 = B[ttb + 2]; //B12

                            // //C00 = A00 * B00 + A01 * B10 + A02 * B20
                            // //B01 = A00 * B01 + A01 * B11 + A02 * B21
                            // C00 += A00*B00;
                            // C01 += A00*B01;
                            // C02 += A00*B02;

                            // C10 += A10*B00;
                            // C11 += A10*B01;
                            // C12 += A10*B02;

                            // C20 += A20*B00;
                            // C21 += A20*B01;
                            // C22 += A20*B02;

                            // A00 = A[ta + 2]; //A02
                            // A10 = A[tta + 2]; //A12
                            // A20 = A[ttta + 2]; //A22

                            // B00 = B[tttb]; //B20
                            // B01 = B[tttb + 1]; //B21
                            // B02 = B[tttb + 2]; //B22   

                            // C00 += A00*B00;
                            // C01 += A00*B01;
                            // C02 += A00*B02;

                            // C10 += A10*B00;
                            // C11 += A10*B01;
                            // C12 += A10*B02;

                            // C20 += A20*B00;
                            // C21 += A20*B01;
                            // C22 += A20*B02; 
                            
                        }

                            C[t] = C00;
                            C[t + 1] = C01;
                            C[t + 2] = C02;
                            C[tt] = C10;
                            C[tt + 1] = C11;
                            C[tt + 2] = C12;
                            C[ttt] = C20;
                            C[ttt + 1] = C21;
                            C[ttt + 2] = C22;;

                    }
                }
            }
        }
    }
}
