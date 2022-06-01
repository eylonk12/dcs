#ifndef _func_H_
#define _func_H_

#define M 10 
#define N 10
#define CEIL 100 
#define max(x,y) x>y ? x : y  // MACRO function

extern char** menu[];

extern int ComputeTrace(int Mat[M][M]);
extern int DiagonalsMax(int Mat[M][M]);
extern void CopyDiagonals(int Mat1[M][M], int Mat2[M][M]);
extern void Transpose(int Mat1[M][M], int Mat2[M][M]);
extern void FillMatrix(unsigned int Mat[M][M], int offset);
extern void SumMatrix(unsigned int Mat1[M][M], unsigned int Mat2[M][M], unsigned int AnsMat[M][M]);
extern void show_matrix(unsigned int Mat[M][M]);


#endif