#ifndef _func_H_
#define _func_H_

#define M 10 
#define N 10
#define CEIL 100 
#define max(x,y) x>y ? x : y  // MACRO function

extern char** menu[];


extern void show_menu(char** strlst);
extern int ComputeTrace(int Mat[M][M]);
extern int DiagonalsMax(int Mat[M][M]);
extern void Transpose(int Mat1[M][M], int Mat2[M][M]);
extern void FillMatrix(unsigned int Mat[M][M], int);
extern void show_matrix(unsigned int Mat[M][M]);
extern void AddMatrix(int Mat1[M][M], int Mat2[M][M], int ans[M][M]);
extern void diagonals_copy_backwards(int Mat1[M][M], int Mat2[M][M]);


#endif

