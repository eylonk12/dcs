#include <stdio.h>
#include <string.h> 
#include "..\header\func.h"     // private library - HAL layer

void show_menu(char** strlst) {
    int i;
    for (i = 0; strlst[i]; i++)
        printf("%s\n", strlst[i]);
    return;
}



char** menu[] = {
    "---------------------- Menu--------------------------------\n\r-----------------------------------------------------------",
    "1) Create two 10x10 matrices Mat1,Mat2  using the next expression: ",
    "   for i,j = {0-9}: Mat[i][j] = (offset + i * 10 + j) % 100",
    "2) Compute and show the matrix Mat1+Mat2",
    "3) Compute and show the maximal diagonal element between Mat1 and Mat2",
    "4) Compute and show the maximal Trace between matrices Mat1 and Mat2",
    "5) Copy Mat1 right diagonals to Mat2 left diagonals",
    "6) Compute and show the transposed of given Matrix",
    "7) Show a given Matrix",
    "8) Show menu",
    "9) exit",
    NULL
};
//---------------------------------------------------------------
//                  Trace Computation
//---------------------------------------------------------------
int ComputeTrace(int Mat[M][M]) {
    int Trace = 0, i;
    for (i = 0; i < M; i++) Trace += Mat[i][i];
    return Trace;
}
//---------------------------------------------------------------
//                  DiagonalsMax Computation
//---------------------------------------------------------------
int DiagonalsMax(int Mat[M][M]) {
    int Max = 0, i;
    for (i = 0; i < M; i++) {
        Max = max(Mat[i][i], Max);
        Max = max(Mat[i][N - 1 - i], Max);
    }
    return Max;
}
//---------------------------------------------------------------
//                  Matrix Transpose 
//---------------------------------------------------------------
void Transpose(int Mat1[M][M], int Mat2[M][M]) {
    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            Mat2[i][j] = Mat1[j][i];
            Mat2[j][i] = Mat1[i][j];
        }
    }
}
//---------------------------------------------------------------
//                  add Matrices
//---------------------------------------------------------------
void AddMatrix(int Mat1[M][M], int Mat2[M][M], int ans[M][M]) {
    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            ans[i][j] = Mat1[i][j] + Mat2[i][j];
        }
    }
}
//---------------------------------------------------------------
//                  Fill Matrix
//---------------------------------------------------------------
void FillMatrix(unsigned int Mat[M][M], int offset) {
    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            Mat[i][j] = (offset + i * M + j) % CEIL;
        }
    }
}
//---------------------------------------------------------------
//                  Diagonals copy backwards
//---------------------------------------------------------------
void diagonals_copy_backwards(int Mat1[M][M], int Mat2[M][M])
{
    int diag1[M], diag2[M], i, j, cnt1 = 0, cnt2 = 0;
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            if (i == j) {
                diag1[cnt1] = Mat1[i][j];
                cnt1++;
            }
            if (i + j == M - 1) {
                diag2[cnt2] = Mat1[i][j];
                cnt2++;
            }
        }
    }
    cnt1 = 0, cnt2 = 0;
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            if (i == j) {
                Mat2[i][j] = diag2[cnt1];
                cnt1++;
            }
            if (i + j == M - 1) {
                Mat2[i][j] = diag1[cnt2];
                cnt2++;
            }
        }
    }
}
//---------------------------------------------------------------
//                  show matrix
//---------------------------------------------------------------
void show_matrix(unsigned int Mat[M][M]) {
    int i, j;
    printf("[\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++)
            printf("%d, ", Mat[i][j]);
        printf("\n");
    }
    printf("]\n\n");
    return;
}