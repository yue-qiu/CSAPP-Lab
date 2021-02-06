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
    if (N == 32) {
        int STEP = 8;
        for (int i = 0; i < N; i += STEP) {
            for (int j = 0; j < M; j += STEP) {
                for (int row = i; row < i + STEP; ++row) {
                    for (int col = j; col < j + STEP; col += STEP) {
                        int tmp0 = A[row][col+0];
                        int tmp1 = A[row][col+1];
                        int tmp2 = A[row][col+2];
                        int tmp3 = A[row][col+3];
                        int tmp4 = A[row][col+4];
                        int tmp5 = A[row][col+5];
                        int tmp6 = A[row][col+6];
                        int tmp7 = A[row][col+7];

                        B[col+0][row] = tmp0;
                        B[col+1][row] = tmp1;
                        B[col+2][row] = tmp2;
                        B[col+3][row] = tmp3;
                        B[col+4][row] = tmp4;
                        B[col+5][row] = tmp5;
                        B[col+6][row] = tmp6;
                        B[col+7][row] = tmp7;
                    }
                }
            }
        }
    } else if (N == 67) {
        int STEP = 17;
        for (int i = 0; i < N; i += STEP) {
            for (int j = 0; j < M; j += STEP) {
                for (int row = i; row < i + STEP && row < N; ++row) {
                    for (int col = j; col < j + STEP && col < M; ++col) {
                        int tmp = A[row][col];
                        B[col][row] = tmp;
                    }
                }
            }
        }
    } else if (N == 64) {
        int STEP = 4;
        for (int i = 0; i < N; i += STEP) {
            for (int j = 0; j < M; j += STEP) {
                for (int row = i; row < i + STEP; ++row) {
                    for (int col = j; col < j + STEP; col += STEP) {
                        int tmp0 = A[row][col+0];
                        int tmp1 = A[row][col+1];
                        int tmp2 = A[row][col+2];
                        int tmp3 = A[row][col+3];

                        B[col+0][row] = tmp0;
                        B[col+1][row] = tmp1;
                        B[col+2][row] = tmp2;
                        B[col+3][row] = tmp3;
                    }
                }
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

