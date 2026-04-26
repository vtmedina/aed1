#include <stdio.h>
#include <stdlib.h>

int** generateMatrix(int n, int* returnSize, int** returnColumnSizes) {
    *returnSize = n;
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        (*returnColumnSizes)[i] = n;
    }

    int** ans = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        ans[i] = (int*)malloc(n * sizeof(int));
    }

    int left = 0, right = n - 1;
    int top = 0, bottom = n - 1;
    int num = 1;

    while (left <= right && top <= bottom) {
        for (int i = left; i <= right; i++) {
            ans[top][i] = num++;
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            ans[i][right] = num++;
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                ans[bottom][i] = num++;
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                ans[i][left] = num++;
            }
            left++;
        }
    }

    return ans;
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int n;
    printf("Digite o valor de n (1 a 20): ");
    scanf("%d", &n);
    
    if (n < 1 || n > 20) {
        printf("Valor invalido! Use n entre 1 e 20.\n");
        return 1;
    }
    
    int returnSize;
    int* returnColumnSizes;
    
    int** result = generateMatrix(n, &returnSize, &returnColumnSizes);
    
    printf("\nMatriz espiral %dx%d:\n\n", n, n);
    printMatrix(result, n);
    
    freeMatrix(result, n);
    free(returnColumnSizes);
    
    return 0;
}