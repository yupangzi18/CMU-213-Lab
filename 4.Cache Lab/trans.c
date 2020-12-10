/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    // 32 x 32
    if(32 == M && 32 == N) {
        int i, j, k;
        int ak0, ak1, ak2, ak3, ak4, ak5, ak6, ak7;

        for (i = 0; i < N; i += 8) {
            for (j = 0; j < M; j += 8) {
                for (k = i; k < i + 8; ++k) {
                    ak0 = A[k][j];
                    ak1 = A[k][j + 1];
                    ak2 = A[k][j + 2];
                    ak3 = A[k][j + 3];
                    ak4 = A[k][j + 4];
                    ak5 = A[k][j + 5];
                    ak6 = A[k][j + 6];
                    ak7 = A[k][j + 7];
                    B[j][k] = ak0;
                    B[j + 1][k] = ak1;
                    B[j + 2][k] = ak2;
                    B[j + 3][k] = ak3;
                    B[j + 4][k] = ak4;
                    B[j + 5][k] = ak5;
                    B[j + 6][k] = ak6;
                    B[j + 7][k] = ak7;
                }
            }
        }
    }

    // 64 x 64
    if (64 == M && 64 == N) {
        int i, j, m, n;
        int val0, val1, val2, val3, val4, val5, val6, val7;
        for (i = 0; i < M; i += 8) {
            for (j = 0; j < N; j += 8) {
                for(m = i; m < i + 4; ++m) {
                    val0 = A[m][j];
                    val1 = A[m][j + 1];
                    val2 = A[m][j + 2];
                    val3 = A[m][j + 3];
                    val4 = A[m][j + 4];
                    val5 = A[m][j + 5];
                    val6 = A[m][j + 6];
                    val7 = A[m][j + 7];

                    B[j][m] = val0;
                    B[j + 1][m] = val1;
                    B[j + 2][m] = val2;
                    B[j + 3][m] = val3;
                    B[j][m + 4] = val4;
                    B[j + 1][m + 4] = val5;
                    B[j + 2][m + 4] = val6;
                    B[j + 3][m + 4] = val7;
                }

                for (n = j; n < j + 4; ++n) {
                    val0 = A[i + 4][n];
                    val1 = A[i + 5][n];
                    val2 = A[i + 6][n];
                    val3 = A[i + 7][n];
                    val4 = B[n][i + 4];
                    val5 = B[n][i + 5];
                    val6 = B[n][i + 6];
                    val7 = B[n][i + 7];

                    B[n][i + 4] = val0;
                    B[n][i + 5] = val1;
                    B[n][i + 6] = val2;
                    B[n][i + 7] = val3;
                    B[n + 4][i] = val4;
                    B[n + 4][i + 1] = val5;
                    B[n + 4][i + 2] = val6;
                    B[n + 4][i + 3] = val7;
                }

                for (m = i + 4; m < i + 8; ++m) {
                    val4 = A[m][j + 4];
                    val5 = A[m][j + 5];
                    val6 = A[m][j + 6];
                    val7 = A[m][j + 7];

                    B[j + 4][m] = val4;
                    B[j + 5][m] = val5;
                    B[j + 6][m] = val6;
                    B[j + 7][m] = val7;
                }
            }
        }
    }

    // 61 x 67
    if(61 == M && 67 == N) {
        int i, j;
        int val0, val1, val2, val3, val4, val5, val6, val7;
        int m = M / 8 * 8;
        int n = N / 8 * 8;

        for (j = 0; j < m; j += 8) {
            for (i = 0; i < n; ++i) {
                val0 = A[i][j];
                val1 = A[i][j + 1];
                val2 = A[i][j + 2];
                val3 = A[i][j + 3];
                val4 = A[i][j + 4];
                val5 = A[i][j + 5];
                val6 = A[i][j + 6];
                val7 = A[i][j + 7];

                B[j][i] = val0;
                B[j + 1][i] = val1;
                B[j + 2][i] = val2;
                B[j + 3][i] = val3;
                B[j + 4][i] = val4;
                B[j + 5][i] = val5;
                B[j + 6][i] = val6;
                B[j + 7][i] = val7;
            }
        }

        for (i = n; i < N; ++i) {
            for (j = m; j < M; ++j) {
                B[j][i] = A[i][j];
            }
        }

        for (i = 0; i < N; ++i) {
            for (j = m; j < M; ++j) {
                B[j][i] = A[i][j];
            }
        }

        for (i = n; i < N; ++i) {
            for (j = 0; j < M; ++j) {
                B[j][i] = A[i][j];
            }
        }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

