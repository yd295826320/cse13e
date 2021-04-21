#include <stdio.h>
#include <math.h>

#include"MatrixMath.h"
#include"BOARD.h"

float result[3][3];
/**
 * MatrixEquals checks if the two matrix arguments are equal (to within FP_DELTA).
 * @param: mat1, pointer to a 3x3 float array
 * @param: mat2, pointer to a 3x3 float array
 * @return: TRUE if and only if every element of mat1 is within FP_DELTA of the corresponding element of mat2,  otherwise return FALSE
 * Neither mat1 nor mat2 is modified by this function.
 */
int MatrixEquals(float mat1[3][3], float mat2[3][3])
{
    int row = 0;
    int col = 0;
    for ( row = 0; row < DIM; row++){
        for ( col = 0; col < DIM; col++){
            if (!(abs(mat1[row][col] - mat2[row][col]) < FP_DELTA))
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}
/**
 * MatrixAdd performs an element-wise matrix addition operation on two 3x3 matrices and 
 * "returns" the result by modifying the third argument.
 * @param: mat1, pointer to a summand 3x3 matrix
 * @param: mat2, pointer to a summand 3x3 matrix
 * @param: result, pointer to a 3x3 matrix that is modified to contain the sum of mat1 and mat2.
 * @return:  None
 * mat1 and mat2 are not modified by this function.  result is modified by this function.
 */
void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int row = 0;
    int col = 0;
    for ( row = 0; row < DIM; row++){
        for ( col = 0; col < DIM; col++){
            result[row][col] = mat1[row][col] + mat2[row][col];
        }
    }
    
}
/**
 * MatrixMultiply performs a matrix-matrix multiplication operation on two 3x3
 * matrices and "returns" the result by modifying the third argument.
 * @param: mat1, pointer to left factor 3x3 matrix
 * @param: mat2, pointer to right factor 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain the matrix product of mat1 and mat2.
 * @return: none
 * mat1 and mat2 are not modified by this function.  result is modified by this function.
 */
void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int row = 0;
    int col = 0;
    int k = 0;
    for ( row = 0; row < DIM; row++){
        for ( col = 0; col < DIM; col++){
            for ( k = 0; k < DIM; k++ ){
               result[row][col] += mat1[row][k] * mat2[k][col]; 
            }
        }
    }
}
/**
 * MatrixScalarAdd performs the addition of a matrix and a scalar.  Each element of the matrix is increased by x.
 * The result is "returned"by modifying the third argument.
 * @param: x, a scalar float
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain mat + x.
 * @return: none
 * x and mat are not modified by this function.  result is modified by this function.
 */
void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    int row = 0;
    int col = 0;
    for ( row = 0; row < DIM; row++){
        for ( col = 0; col < DIM; col++){
            result[row][col] = mat[row][col] + x;
        }
    }
}
/**
 * MatrixScalarAdd performs the multiplication of a matrix and a scalar.
 * Each element of the matrix is multiplied x.
 * The result is "returned"by modifying the third argument.
 * @param: x, a scalar float
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain mat + x.
 * @return: none
 * x and mat are not modified by this function.  result is modified by this function.
 */
void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    int row = 0;
    int col = 0;
    for ( row = 0; row < DIM; row++){
        for ( col = 0; col < DIM; col++){
            result[row][col] = mat[row][col] * x;
        }
    }
}
/**
 * MatrixTrace calculates the trace of a 3x3 matrix.
 * @param: mat, a pointer to a 3x3 matrix
 * @return: the trace of mat
 */
float MatrixTrace(float mat[3][3])
{
    int row;
    float trace = 0;
    for ( row = 0; row < DIM; row++){
        trace += mat[row][row];
    }
    
    return trace;
}
/**
 * MatrixTranspose calculates the transpose of a matrix and "returns" the
 * result through the second argument.
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to transpose of mat
 * mat is not modified by this function.  result is modified by this function.
 */
void MatrixTranspose(float mat[3][3], float result[3][3])
{
    int row = 0;
    int col = 0;
     for ( row = 0; row < DIM; row++){
        for ( col = 0; col < DIM; col++){
            result[col][row] = mat[row][col] ;
        }
    }
}
/**
 * MatrixSubmatrix finds a submatrix of a 3x3 matrix that is 
 * formed by removing the i-th row and the j-th column.  The 
 * submatrix is "returned" by modifying the final argument.
 * 
 * @param: i, a row of the matrix, INDEXING FROM 0
 * @param: j, a column of the matrix, INDEXING FROM 0
 * @param: mat, a pointer to a 3x3 matrix
 * @param: result, a pointer to a 2x2 matrix
 * @return: none
 * 
 * mat is not modified by this function.  Result is modified by this function.
 */
void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2])
{
    if (i == 0 && j == 0){
        result[0][0] = mat[1][1];
        result[0][1] = mat[1][2];
        result[1][0] = mat[2][1];
        result[1][1] = mat[2][2];
    }
    if (i == 0 && j == 1){
        result[0][0] = mat[1][0];
        result[0][1] = mat[1][2];
        result[1][0] = mat[2][0];
        result[1][1] = mat[2][2];
    }
    if (i == 0 && j == 2){
        result[0][0] = mat[1][0];
        result[0][1] = mat[1][1];
        result[1][0] = mat[2][0];
        result[1][1] = mat[2][1];
    }
    if (i == 1 && j == 0){
        result[0][0] = mat[0][1];
        result[0][1] = mat[0][2];
        result[1][0] = mat[2][1];
        result[1][1] = mat[2][2];
    }
    if (i == 1 && j == 1){
        result[0][0] = mat[0][0];
        result[0][1] = mat[0][2];
        result[1][0] = mat[2][0];
        result[1][1] = mat[2][2];
    }
    if (i == 1 && j == 2){
        result[0][0] = mat[0][0];
        result[0][1] = mat[0][1];
        result[1][0] = mat[2][0];
        result[1][1] = mat[2][1];
    }
    if (i == 2 && j == 0){
        result[0][0] = mat[0][1];
        result[0][1] = mat[0][2];
        result[1][0] = mat[1][1];
        result[1][1] = mat[1][2];
    }
    if (i == 2 && j == 1){
        result[0][0] = mat[0][0];
        result[0][1] = mat[0][2];
        result[1][0] = mat[1][0];
        result[1][1] = mat[1][2];
    }
    if (i == 2 && j == 2){
        result[0][0] = mat[0][0];
        result[0][1] = mat[0][1];
        result[1][0] = mat[1][0];
        result[1][1] = mat[1][1];
    }
    
}
/**
 * for ( row = 0;row < DIM; row++){                //inside if equal to i and j then skp;
        for ( col = 0; col < DIM; col++){
            if (row == i || col == j){
                 continue; 
            }
            else{
                for ( a = 0; a < 2; a++){                
                    for ( b = 0; b < 2; b++){
                        result[a][b] += mat[row][col];  
                    }
                }
            }
        }
    }
 * MatrixDeterminant calculates the determinant of a 3x3 matrix 
 * and returns the value as a float.
 * @param: mat, a pointer to a 2x2 matrix
 * @return: the determinant of mat
 * mat is not modified by this function.
 * 
 float MatrixDeterminant2x2(int i, int j, float mat[3][3])
{
    float det2;
    MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2]);
    det2 = result[0][0] * result[1][1] + result[0][1] * result[1][0];
    return det2;
}*/

/**
 * MatrixDeterminant calculates the determinant of a 3x3 matrix 
 * and returns the value as a float.
 * @param: mat, a pointer to a 3x3 matrix
 * @return: the determinant of mat
 * mat is not modified by this function.
 * */
float MatrixDeterminant(float mat[3][3])
{
    float det;
    float det1 = 0;
    float det2 = 0;
    float det3 = 0;
    float result_1[2][2] = {{0,0},{0,0}};
    float result_2[2][2] = {{0,0},{0,0}};
    float result_3[2][2] = {{0,0},{0,0}};
    MatrixSubmatrix(0, 0, mat, result_1);
    det1 = (result_1[0][0] * result_1[1][1]) + (result_1[0][1] * result_1[1][0]);
    MatrixSubmatrix(0, 1, mat, result_2);
    det2 = (result_2[0][0] * result_2[1][1]) + (result_2[0][1] * result_2[1][0]);
    MatrixSubmatrix(0, 2, mat, result_3);
    det3 = (result_3[0][0] * result_3[1][1]) + (result_3[0][1] * result_3[1][0]);
    
    det = det1 * mat[0][0] - det2 * mat[0][1] + det3 * mat[0][2];
    
    return det;
}
/* int i;
    int j;
    float x;
    float y;
    float z;
    float det;
    float det2;
    det2 = MatrixDeterminant2x2(int i = 0, int j = 0, float mat[3][3]);
    x = mat[0][0] * det2;
    det2 = MatrixDeterminant2x2(int i = 0, int j = 1, float mat[3][3]);
    y = mat[0][1] * det2;
    det2 = MatrixDeterminant2x2(int i = 0, int j = 2, float mat[3][3]);
    z = mat[0][2] * det2;
    det = x - y + z;
 * MatrixInverse calculates the inverse of a matrix and
 * "returns" the result by modifying the second argument.
 * @param: mat, a pointer to a 3x3 matrix
 * @param: result, a pointer to a 3x3 matrix that is modified to contain the inverse of mat
 * @return: none
 * mat is not modified by this function.  result is modified by this function.
 */
void MatrixInverse(float mat[3][3], float result[3][3]) 
{
    float cofactor[DIM][DIM] = {{0,0,0},{0,0,0},{0,0,0}};
    float det;
    float x = 0;
    float result_sub[2][2] = {{0,0},{0,0}};
    int row = 0, col = 0, det1 = 0;
    for ( row = 0; row < DIM; row++){
        for (col = 0; col < DIM; col++){
            if ((row + col) % 2 == 0){
                MatrixSubmatrix(row, col, mat, result_sub);
                det1 = result_sub[0][0] * result_sub[1][1] + result_sub[0][1] * result_sub[1][0];
                cofactor[row][col] = det1; 
            }
            else{
                MatrixSubmatrix(row, col, mat, result_sub);
                det1 = result_sub[0][0] * result_sub[1][1] + result_sub[0][1] * result_sub[1][0];
                cofactor[row][col] = -1 * det1;
            }
        }
    }
    det = MatrixDeterminant(mat);
    x = 1 / det;
    MatrixScalarMultiply(x, cofactor, result);
}
/**
 * MatrixPrint displays a 3x3 array to standard output with clean, readable, 
 * 
 * consistent formatting.  
 * @param: mat, pointer to a 3x3 float array
 * @return: none
 * The printed matrix should be aligned in a grid when called with positive or
 *  negative numbers.  It should be able to display at least FP_DELTA precision, and
 *  should handle numbers as large as 999.0 or -999.0
 */
void MatrixPrint(float mat[3][3])

{
    printf("----------------------------------\n");
    printf("| %f | %f | %f |\n",mat[0][0],mat[0][1],mat[0][2]);
    printf("----------------------------------\n");
    printf("| %f | %f | %f |\n",mat[1][0],mat[1][1],mat[1][2]);
    printf("----------------------------------\n");
    printf("| %f | %f | %f |\n",mat[2][0],mat[2][1],mat[2][2]);
    printf("----------------------------------\n");

    
}