#include <stdio.h>

void matrixMulti(int r1, int c1, int m1[r1][c1], 
                      int r2, int c2, int m2[r2][c2], 
                      int result[r1][c2]) {
   
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
        }
    }

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

int main() {
    int r1, c1, r2, c2;

    printf("Enter the rows and columns for the first matrix: ");
    scanf("%d %d", &r1, &c1);

    
    printf("Enter the rows and columns for the second matrix: ");
    scanf("%d %d", &r2, &c2);

    if (c1 != r2) {
        printf("Matrix multiplication is not possible. cuz dimension is different.\n");
        return 1;
    }

    
    int m1[r1][c1], m2[r2][c2], result[r1][c2];

    
    printf("Enter elements of the first matrix:\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            scanf("%d", &m1[i][j]);
        }
    }

    
    printf("Enter elements of the second matrix:\n");
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            scanf("%d", &m2[i][j]);
        }
    }

    
    matrixMulti(r1, c1, m1, r2, c2, m2, result);
    printf("Resultant matrix :\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}