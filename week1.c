#include<stdio.h>
#include<stdlib.h>
#define maxsize 100
void addMatrix(int row, int col, int matrix1[maxsize][maxsize], int matrix2[maxsize][maxsize]);
void subtractMatrix(int row, int col, int matrix1[maxsize][maxsize], int matrix2[maxsize][maxsize]);
void multiplyScalar(int row, int col, int matrix[maxsize][maxsize], int scalar);
void multiplyMatrix(int row1, int col1, int matrix1[maxsize][maxsize], int row2, int col2, int matrix2[maxsize][maxsize]);
void divideByScalar(int row, int col, int matrix[maxsize][maxsize], int scalar);
void divideByMatrix(int row1, int col1, int matrix1[maxsize][maxsize], int row2, int col2, int matrix2[maxsize][maxsize]);
void transpose(int row, int col, int matrix[maxsize][maxsize]);
int determinant(int n, int matrix[maxsize][maxsize]);
void getCofactor(int n, int matrix[maxsize][maxsize], int temp[maxsize][maxsize], int p, int q);
void adjoint(int n, int matrix[maxsize][maxsize], int adj[maxsize][maxsize]);
void inverse(int n, int matrix[maxsize][maxsize]);
void displayMatrix(int row, int col, int matrix[maxsize][maxsize]);
void addMatrix(int row, int col, int matrix1[maxsize][maxsize], int matrix2[maxsize][maxsize]) {
    int result[maxsize][maxsize];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    displayMatrix(row, col, result);
}

void subtractMatrix(int row, int col, int matrix1[maxsize][maxsize], int matrix2[maxsize][maxsize]) {
    int result[maxsize][maxsize];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }

    displayMatrix(row, col, result);
}

void multiplyScalar(int row, int col, int matrix[maxsize][maxsize], int scalar) {
    int result[maxsize][maxsize];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }

    displayMatrix(row, col, result);
}

void multiplyMatrix(int row1, int col1, int matrix1[maxsize][maxsize], int row2, int col2, int matrix2[maxsize][maxsize]) {
    int result[maxsize][maxsize];

    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < col1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    displayMatrix(row1, col2, result);
}

void divideByScalar(int row, int col, int matrix[maxsize][maxsize], int scalar) {
    int result[maxsize][maxsize];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            result[i][j] = matrix[i][j] / scalar;
        }
    }

    displayMatrix(row, col, result);
}

void divideByMatrix(int row1, int col1, int matrix1[maxsize][maxsize], int row2, int col2, int matrix2[maxsize][maxsize]) {
    int result[maxsize][maxsize];

    //col1 == row2 for valid division
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < col1; k++) {
                result[i][j] += matrix1[i][k] / matrix2[k][j];
            }
        }
    }

    displayMatrix(row1, col2, result);
}

void transpose(int row, int col, int matrix[maxsize][maxsize]) {
    int result[maxsize][maxsize];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            result[j][i] = matrix[i][j];
        }
    }

    displayMatrix(col, row, result);
}

int determinant(int n, int matrix[maxsize][maxsize]) {
    int det = 0;
    if (n == 1) {
        return matrix[0][0];
    } else if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    } else {
        int temp[maxsize][maxsize];
        int sign = 1;
        for (int f = 0; f < n; f++) {
            getCofactor(n, matrix, temp, 0, f);
            det += sign * matrix[0][f] * determinant(n - 1, temp);
            sign = -sign;
        }
    }
    return det;
}

void getCofactor(int n, int matrix[maxsize][maxsize], int temp[maxsize][maxsize], int p, int q) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = matrix[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void adjoint(int n, int matrix[maxsize][maxsize], int adj[maxsize][maxsize]) {
    if (n == 1) {
        adj[0][0] = 1;
        return;
    }
    int sign = 1;
    int temp[maxsize][maxsize];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            getCofactor(n, matrix, temp, i, j);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = sign * determinant(n - 1, temp);
        }
    }
}

void inverse(int n, int matrix[maxsize][maxsize]) {
    int det = determinant(n, matrix);
    if (det == 0) {
        printf("Matrix inversion is not possible. The matrix is singular.\n");
        return;
    }

    int adj[maxsize][maxsize];
    adjoint(n, matrix, adj);

    int result[maxsize][maxsize];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = adj[i][j] / det;
        }
    }

    displayMatrix(n, n, result);
}

void displayMatrix(int rows, int cols, int matrix[maxsize][maxsize]) {
    printf("Resultant Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int row1, col1, row2, col2;
    int matrix1[maxsize][maxsize], matrix2[maxsize][maxsize];
    int choice, scalar;

    printf("Enter the number of rows and columns for the first matrix");
    scanf("%d %d", &row1, &col1);

    printf("Enter the elements of the first matrix:\n");
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            scanf("%d", &matrix1[i][j]);
        }
    }

    printf("Enter the number of rows and columns for the second matrix");
    scanf("%d %d", &row2, &col2);

    printf("Enter the elements of the second matrix:\n");
    for (int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            scanf("%d", &matrix2[i][j]);
        }
    }

    printf("Choose a matrix operation:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication with a scalar\n");
    printf("4. Multiplication with a matrix\n");
    printf("5. Division by a scalar\n");
    printf("6. Division by a matrix\n");
    printf("7. Transpose of the first matrix\n");
    printf("8. Inverse of the first matrix\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            if (row1 != row2 || col1 != col2) {
                printf("Matrix addition is not possible.\n");
            } else {
                addMatrix(row1, col1, matrix1, matrix2);
            }
            break;

        case 2:
            if (row1 != row2 || col1 != col2) {
                printf("Matrix subtraction is not possible.\n");
            } else {
                subtractMatrix(row1, col1, matrix1, matrix2);
            }
            break;

        case 3:
            printf("Enter the scalar value: ");
            scanf("%d", &scalar);
            multiplyScalar(row1, col1, matrix1, scalar);
            break;

        case 4:
            if (col1 != row2) {
                printf("Matrix multiplication is not possible. The number of columns in the first matrix should be equal to the number of rows in the second matrix.\n");
            } else {
                multiplyMatrix(row1, col1, matrix1, row2, col2, matrix2);
            }
            break;

        case 5:
            printf("Enter the scalar value: ");
            scanf("%d", &scalar);
            divideByScalar(row1, col1, matrix1, scalar);
            break;

        case 6:
            if (col1 != row2) {
                printf("Matrix division is not possible. The number of columns in the first matrix should be equal to the number of rows in the second matrix.\n");
            } else {
                divideByMatrix(row1, col1, matrix1, row2, col2, matrix2);
            }
            break;

        case 7:
            transpose(row1, col1, matrix1);
            break;

        case 8:
            if (row1 != col1) {
                printf("Matrix inversion is not possible. The matrix should be square.\n");
            } else {
                inverse(row1, matrix1);
            }
            break;

        default:
            printf("Invalid choice.\n");
    }

    return 0;
}


