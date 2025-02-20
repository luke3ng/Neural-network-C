#include <stdio.h>
#include <stdlib.h>

void matrixMultiplication(float** a, float** b, float** result, int aRow, int aCol, int bRow, int bCol) {
    if (aCol != bRow) {
        return;
    }

    for (int i = 0; i < aRow; i++) {
        for (int j = 0; j < bCol; j++) {
            result[i][j] = 0;
            for (int k = 0; k < aCol; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void swapRows(float** a, int cols, int row1, int row2) {
    float* temp = a[row1];
    a[row1] = a[row2];
    a[row2] = temp;
}

void addRows(float** a, int cols, int row1, int row2, float stcalar) {
    for (int i = 0; i < cols; i++) {
        a[row1][i] += scalar * a[row2][i];
    }
}

float** rref(float** a, int rows, int cols) {
    int lead = 0;
    for (int r = 0; r < rows; r++) {
        if (lead >= cols) {
            return a;
        }

        int i = r;
        while (a[i][lead] == 0) {
            i++;
            if (i == rows) {
                i = r;
                lead++;
                if (lead == cols) {
                    return a;
                }
            }
        }

        swapRows(a, cols, i, r);

        float pivot = a[r][lead];
        if (pivot != 0) {
            for (int j = 0; j < cols; j++) {
                a[r][j] /= pivot;
            }
        }


        for (int k = 0; k < rows; k++) {
            if (k != r) {
                float factor = a[k][lead];
                for (int j = 0; j < cols; j++) {
                    a[k][j] -= factor * a[r][j];
                }
            }
        }

        lead++;
    }
    return a;
}

float** matrixAddition(float** a, float** b, int rows, int cols, int add) {
    float** result = createMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (add == 1) {
                result[i][j] = a[i][j] + b[i][j];
            } else {
                result[i][j] = a[i][j] - b[i][j];
            }
        }
    }
    return result;
}
float determinant(float** a, int size) {
    float** temp = createMatrix(size, size);


    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            temp[i][j] = a[i][j];
        }
    }

    int swaps = 0;
    float det = 1;

    for (int col = 0; col < size; col++) {
        int pivotRow = col;
        while (pivotRow < size && temp[pivotRow][col] == 0) {
            pivotRow++;
        }

        if (pivotRow == size) { 
            freeMatrix(temp, size);
            return 0;
        }

        if (pivotRow != col) {
            swapRows(temp, size, col, pivotRow);
            swaps++;
        }

        float pivot = temp[col][col];
        det *= pivot;

        for (int j = col; j < size; j++) {
            temp[col][j] /= pivot;
        }

        for (int i = col + 1; i < size; i++) {
            float factor = temp[i][col];
            for (int j = col; j < size; j++) {
                temp[i][j] -= factor * temp[col][j];
            }
        }
    }

    if (swaps % 2 != 0) {
        det *= -1;
    }

    freeMatrix(temp, size);
    return det;
}

float** identity( int i){
    float**  iMat = createMatrix(i,i);
   
    for(int j = 0; j < i; j++){
        for(int k = 0; k < i; k++){
            if(k == j){
                iMat[j][k] = 1;
            }
            else{
            iMat[j][k] = 0;
            }



            
        }

    }
    return iMat;

}

float** inverse(float** a, int i) {
    if (determinant(a, i) == 0) {
        return NULL;
    }

    // Create the augmented matrix [A | I]
    float** aug = createMatrix(i, i * 2);
    float** iMat = identity(i);

    for (int row = 0; row < i; row++) {
        for (int col = 0; col < i * 2; col++) {
            if (col < i) {
                aug[row][col] = a[row][col];  // Copy A
            } else {
                aug[row][col] = iMat[row][col - i];  
            }
        }
    }


    freeMatrix(iMat, i);

    aug = rref(aug, i, i * 2);


    float** inverse = createMatrix(i, i);
    for (int row = 0; row < i; row++) {
        for (int col = 0; col < i; col++) {
            inverse[row][col] = aug[row][col + i];
        }
    }


    freeMatrix(aug, i);

    return inverse;
}

float** createMatrix(int rows, int cols) {
    float** array = malloc(rows * sizeof(float*));
    for (int i = 0; i < rows; i++) {
        array[i] = malloc(cols * sizeof(float));
    }
    return array;
}

void freeMatrix(float** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void printMatrix(float** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    return 0;
}
