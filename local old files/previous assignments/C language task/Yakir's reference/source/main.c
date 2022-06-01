#include <stdio.h>
#include <string.h> 
#include "..\header\func.h"     // private library - HAL layer



int main() {
    int Mat1[M][M], Mat2[M][M], auxMat[M][M], ans[M][M];
    int matTrace, maxDiag, maxDiagMatNum, offset1 = 0, offset2 = 0;
    char Selector = '0', ch, str[5], chars[100];

    show_menu(menu);

    while (1) {
        printf("Choose a menu clause number: ");
        Selector = getchar();
        gets(chars);
        switch (Selector) {
        case '0':
            break;

        case '1':
            do {
                printf("In order to creat Mat1 please insert an offset value between 0-100: ");
                gets(str);
                sscanf_s(str, "%d", &offset1);
                if (offset1 >= 0 && offset1 <= 100) break;

            } while (1);
            do {
                printf("In order to creat Mat2 please insert an offset value between 0-100: ");
                gets(str);
                sscanf_s(str, "%d", &offset2);
                if (offset2 >= 0 && offset2 <= 100) break;
            } while (1);
            FillMatrix(Mat1, offset1);
            FillMatrix(Mat2, offset2);
            break;

        case '2':
            AddMatrix(Mat1, Mat2, ans);
            show_matrix(ans);
            break;

        case '3':
            maxDiag = max(DiagonalsMax(Mat1), DiagonalsMax(Mat2));
            if (maxDiag == DiagonalsMax(Mat1)) {
                maxDiagMatNum = 1;
            }
            if (maxDiag == DiagonalsMax(Mat2)) {
                maxDiagMatNum = 2;
            }
            printf("mat%d has the maximal diagonal element value: %d\n", maxDiagMatNum, maxDiag);
            break;

        case '4':
            matTrace = max(ComputeTrace(Mat1), ComputeTrace(Mat2));
            if (matTrace == ComputeTrace(Mat1)) {
                maxDiagMatNum = 1;
            }
            if (matTrace == ComputeTrace(Mat2)) {
                maxDiagMatNum = 2;
            }
            printf("mat%d has the maximal trace value: %d\n", maxDiagMatNum, matTrace);
            break;

        case '5':
            diagonals_copy_backwards(Mat1, Mat2);
            break;

        case '6':
            do {
                printf("Insert the wanted matrix [Mat1 or Mat2]: ");
                gets(str);
                if (strcmp(str, "Mat1") == 0) {
                    Transpose(Mat1, ans);
                    break;
                }
                if (strcmp(str, "Mat2") == 0) {
                    Transpose(Mat2, ans);
                    break;
                }
            } while (1);
            show_matrix(ans);
            break;

        case '7':
            do {
                printf("Insert the wanted matrix [Mat1 or Mat2]: ");
                gets(str);
                if (strcmp(str, "Mat1") == 0) {
                    show_matrix(Mat1);
                    break;
                }
                if (strcmp(str, "Mat2") == 0) {
                    show_matrix(Mat2);
                    break;
                }
            } while (1);
            break;

        case '8':
            show_menu(menu);
            break;

        case '9':
            exit(0);
        default:
            printf("Try agian, You have inserted wrong number\n");
            break;
        }
    }
}