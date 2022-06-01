#include <stdio.h>
#include <string.h>
#include "func.h"     // private library - HAL layer

void show_menu(char** strlst) {
    int i;
    for (i = 0; strlst[i]; i++)
        printf("%s\n", strlst[i]);
    return;
}

char** menu[] = {
    " --------------------- Menu --------------------------------\n\r -----------------------------------------------------------",
    "1) Create two 10x10 matrices Mat1,Mat2 using the next expression:",
    "   for i,j = {0-9}: Mat[i][j] = (offset + i * 10 + j) % 100",
    "2) Compute and show the materix Mat1+Mat2",
    "3) Compute and show the maximal diagonal element between Mat1 and Mat2",
    "4) Compute and show the the maximal Trace between matrices Mat1 and Mat2",
    "5) Copy mat1 right diagonals to mat2 left diagonals",
    "6) Compute and show the transposed of a given Matrix",
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
//                  Copy diagonals
//---------------------------------------------------------------
void CopyDiagonals(int Mat1[M][M], int Mat2[M][M]) {
    int i, j;
    for (i = 0; i < M; i++) {
        Mat2[i][i]         = Mat1[i][N-1 - i];
        Mat2[i][N - 1 - i] = Mat1[i][i];
    }
}
//---------------------------------------------------------------
//                  Matrix Transpose 
//---------------------------------------------------------------
void Transpose(int Mat[M][M], int AnsMat[M][M]) {
    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            AnsMat[i][j] = Mat[j][i];
            AnsMat[j][i] = Mat[i][j];
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
//                  Sum Matrices
//---------------------------------------------------------------
void SumMatrix(unsigned int Mat1[M][M], unsigned int Mat2[M][M], unsigned int AnsMat[M][M]) {
    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            AnsMat[i][j] = Mat1[i][j] + Mat2[i][j];
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


