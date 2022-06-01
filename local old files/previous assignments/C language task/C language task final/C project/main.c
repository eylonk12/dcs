#include <stdio.h>
#include <string.h> 
#include "func.h"     // private library - HAL layer

int main() {

	int Mat1[M][M], Mat2[M][M], AnsMat[M][M];
	int matTrace, maxDiag, offset = 0, MaxDiagElement, MaxTraceElement;
	char Selector = '0', ch, str[5], temp[100];

	show_menu(menu);

	while (1) {

		printf("Choose a menu clause number: ");
		Selector = getchar();
		gets(temp);

		switch (Selector) {
		case '0':
			break;
		case '1':
			do {
				printf("In order to creat Mat1 please insert an offset value between 0-100: ");
				gets(str);
				sscanf_s(str, "%d", &offset);
				if (offset >= 0 && offset <= 100) break;
			} while (1);
			FillMatrix(Mat1, offset);
            do {
                printf("In order to creat Mat2 please insert an offset value between 0-100: ");
                gets(str);
                sscanf_s(str, "%d", &offset);
                if (offset >= 0 && offset <= 100) {
                    break;
                }
            } while (1);
            FillMatrix(Mat2, offset);
			break;

		case '2':
            SumMatrix(Mat1, Mat2, AnsMat);
            show_matrix(AnsMat);
			break;
		case '3':
            MaxDiagElement = max(DiagonalsMax(Mat1), DiagonalsMax(Mat2));
            if (MaxDiagElement == DiagonalsMax(Mat2)) {
                printf("mat2 has the maximal diagonal element value: %d\n", MaxDiagElement);
            }
            else if (MaxDiagElement == DiagonalsMax(Mat1)) {
                printf("mat1 has the maximal diagonal element value: %d\n", MaxDiagElement);
            }
			break;
		case '4':
             MaxTraceElement = max(ComputeTrace(Mat1), ComputeTrace(Mat2));
            if (MaxTraceElement == ComputeTrace(Mat2)) {
                printf("mat2 has the maximal Trace value: %d\n", MaxTraceElement);
            }
            else if (MaxTraceElement == ComputeTrace(Mat1)) {
                printf("mat1 has the maximal Trace value: %d\n", MaxTraceElement);
            }
            break;
		case '5':
            CopyDiagonals(Mat1, Mat2);
			break;
		case '6':
            do {
                printf("Insert the wanted matrix [Mat1 or Mat2]: ");
                gets(str);
                if (strcmp(str, "Mat1") == 0) {
                    Transpose(Mat1, AnsMat);
                    break;
                }
                if (strcmp(str, "Mat2") == 0) {
                    Transpose(Mat2, AnsMat);
                    break;
                }
            } while (1);
            show_matrix(AnsMat);
            break;
		case '7':
            do {
                printf("Insert the wanted matrix [Mat1 or Mat2]: ");
                gets(str);
                if (strcmp(str,  "Mat1") == 0) {
                    show_matrix(Mat1);
                    break;
                }
                if (strcmp(str,  "Mat2") == 0) {
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
			printf("Try agian, You have inserted wrong choise number\n");
			break;
		}
	}
}
