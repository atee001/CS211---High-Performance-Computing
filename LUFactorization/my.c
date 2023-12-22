#ifndef __MY_C__
#define __MY_C__

#include "include.h"

int mydgetrf(double *A, int *ipiv, int n)
{
    double tempv[n];
    int maxind, temps;
    double max;
    // TODO

    for (int i = 0; i < n - 1; i++)
    { // pivoting
        maxind = i;
        max = fabs(A[i * n + i]);
        for (int t = i + 1; t < n; t++)
        {
            if (fabs(A[t * n + i]) > max)
            {
                maxind = t;
                max = fabs(A[t * n + i]);
            }
        }
        if (max == 0)
        {
            return 0;
        }
        else
        {
            if (maxind != i)
            {
                temps = ipiv[i];
                ipiv[i] = ipiv[maxind];
                ipiv[maxind] = temps;
                // swap rows
                memcpy(tempv, &A[i * n], n * sizeof(double));
                memcpy(&A[i * n], &A[maxind * n], n * sizeof(double));
                memcpy(&A[maxind * n], tempv, n * sizeof(double));
            }
        }

        for (int j = i + 1; j < n; j++)
        {
            A[j * n + i] = A[j * n + i] / A[i * n + i];
            for (int k = i + 1; k < n; k++)
            {
                A[j * n + k] = A[j * n + k] - (A[j * n + i] * A[i * n + k]);
            }
        }
    }
    return 1;
}

void mydtrsv(char UPLO, double *A, double *B, int n, int *ipiv)
{
    // TODO
    // forward substitution

    static double *y = NULL;
    if (UPLO == 'L')
    {
        if (y == NULL)
        {
            y = (double *)malloc(n * sizeof(double));
        }

        y[0] = B[ipiv[0]];

        for (int i = 1; i < n; i++)
        {
            double sum = 0.0;
            for (int j = 0; j < i; j++)
            {
                sum += y[j] * A[i * n + j];
            }
            y[i] = B[ipiv[i]] - sum;
        }
    }

    else if (UPLO == 'U')
    {

        double x[n];
        x[n - 1] = y[n - 1] / A[(n * n) - 1];

        for (int i = n - 2; i >= 0; i--)
        {
            double sum = 0.0;
            for (int j = i + 1; j < n; j++)
            {
                sum += x[j] * A[i * n + j];
            }
            x[i] = (y[i] - sum) / A[i * n + i];
        }

        memcpy(B, x, n * sizeof(double));

        if (y != NULL)
        {
            free(y);
            y = NULL;
        }
    }
}

void my_f(double *A, double *B, int n)
{
    int *ipiv = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        ipiv[i] = i;
    if (mydgetrf(A, ipiv, n) == 0)
    {
        printf("LU factoration failed: coefficient matrix is singular.\n");
        return;
    }
    mydtrsv('L', A, B, n, ipiv);
    mydtrsv('U', A, B, n, ipiv);
}

#endif