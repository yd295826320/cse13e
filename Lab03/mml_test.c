// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"




// User libraries:
#include "MatrixMath.h"


// Module-level variables:
float mat_1[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
float mat_2[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
float mat_3[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
float mat_4[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
float mat_5[3][3] = {{6,6,6},{15,15,15},{24,24,24}};
float mat_6[3][3] = {{1,4,7},{2,5,8},{3,6,9}};
float mat_7[3][3] = {{0,1,1},{1,0,1},{1,1,0}};
float mat_8[3][3] = {{1,3,4},{5,5,7},{8,9,9}};
float mat_9[3][3] = {{5,4,3},{11,10,9},{17,16,15}};
float mat_10[3][3] = {{-0.5,0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,-0.5}};
float mat_11[3][3] = {{7,2,1},{0,3,-1},{-3,4,-2}};
float mat_12[3][3] = {{-2,8,-5},{3,-11,7},{9,-34,21}};
float result[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
float zero_mat[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
float zero_mat2[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
float zero_mat3[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
float zero_mat4[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
float x;
float y;
float ind = 0;
float trace;
float det;
int p;
int main()
{
    BOARD_Init();

    printf("Beginning dyu33's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);
    
    //printf("Demonstrating MatrixPrint():\n");
    //MatrixPrint(mat1);
    // Add more tests here!
    //MatrixEquals*************************************************************
    if (MatrixEquals(mat_1, mat_2) && !(MatrixEquals(mat_1, mat_3))){            
        ind += 1;
        printf("PASSED (2/2):MatrixEquals\n");
    }
    //MatrixAdd*****************************************************************
    MatrixAdd(mat_1,mat_3,zero_mat);                                                                 
    if (MatrixEquals(mat_2, zero_mat)){
        ind += 0.5;
        p += 1;
    }
    MatrixAdd(mat_1,mat_7,zero_mat);                                                                 
    if (MatrixEquals(mat_8, zero_mat)){
        ind += 0.5;
        p += 1;
    }
    printf("PASSED (%d/2):MatrixAdd\n",p);
    p = 0;
    
    
    //multiply*****************************************************************
    MatrixMultiply(mat_1,mat_4,result);                             
    if (MatrixEquals(mat_5, result)){
        ind += 0.5;
        p += 1;
    }
    MatrixMultiply(mat_2,mat_7,zero_mat2);                             
    if (MatrixEquals(mat_9, zero_mat2)){
        ind += 0.5;
        p += 1;
    }
    printf("PASSED (%d/2):MatrixMultiply\n",p);
    p = 0;
    
    
    //scalar add***************************************************************
    MatrixScalarAdd(1, mat_3, zero_mat);                             
    if (MatrixEquals(mat_4, zero_mat)){
        ind += 0.5;
        p += 1;
    }
    MatrixScalarAdd(-1, mat_4, zero_mat);                             
    if (MatrixEquals(mat_3, zero_mat)){
        ind += 0.5;
        p += 1;
    }
    printf("PASSED (%d/2):MatrixScalarAdd\n",p);
    p = 0;
    
    
    //scalar multiply**********************************************************
    MatrixScalarMultiply(1,mat_1,zero_mat);                          
    if (MatrixEquals(mat_2, zero_mat)){
        ind += 0.5;
        p += 1;
    }
    MatrixScalarMultiply(0,mat_5,zero_mat);                          
    if (MatrixEquals(mat_3, zero_mat)){
        ind += 0.5;
        p += 1;
    }
    printf("PASSED (%d/2):MatrixScalarMultiply\n",p);
    p = 0;
     
     
    //trace********************************************************************
    x = MatrixTrace(mat_4);                                                                                   
    if (x == 3){
        ind += 0.5;
        p += 1;
    }
    y = MatrixTrace(mat_1);
    if ( y == 15.0){
        ind += 0.5;
        p += 1;
    }
    
    printf("PASSED (%d/2):MatrixTrace\n",p);
    x = 0;
    y = 0;
    p = 0;
    
     //transpose***************************************************************
    MatrixTranspose(mat_2,zero_mat);                                   
    if (MatrixEquals(mat_6, zero_mat)){
        ind += 0.5;
        p += 1;
    }
    MatrixTranspose(mat_6,zero_mat);                                   
    if (MatrixEquals(mat_2, zero_mat)){
        ind += 0.5;
        p += 1;
    }
    printf("PASSED (%d/2):MatrixTranspose\n",p);
    p = 0;
    
    
    //det**********************************************************************
    x = MatrixDeterminant(mat_1);                                                                   
    if (x == 0){
        ind += 0.5;
        p += 1;;
    }
    y = MatrixDeterminant(mat_7); 
    if (y == 2){
        ind += 0.5;
        p += 1;;
    }
    printf("PASSED (%d/2):MatrixDeterminant\n",p);
    x = 0;
    y = 0;
    p = 0;
    
    
    //inverse******************************************************************
    MatrixInverse(mat_7,zero_mat3);
    if (MatrixEquals(mat_10, zero_mat3)){
        ind += 0.5;
        p += 1;
    }
    MatrixInverse(mat_11,zero_mat4);
    if (MatrixEquals(mat_12, zero_mat4)){
        ind += 0.5;
        p += 1;
    }
    printf("PASSED (%d/2):MatrixInverse\n",p);
    p = 0;
    
    //print result**************************************************************
    x = (ind / 9) * 100 ;
    
    printf("%.1f out of 9 functions passed(%.0f%%)\n", ind,x);                  //percentage
    
    printf("OUTPUT OF MatrixPrint:\n");
    MatrixPrint(mat_1);
    printf("EXPECTED OUTPUT OF MatrixPrint:\n");
    printf("----------------------------------\n");
    printf("| %f | %f | %f |\n",mat_1[0][0],mat_1[0][1],mat_1[0][2]);
    printf("| %f | %f | %f |\n",mat_1[1][0],mat_1[1][1],mat_1[1][2]);
    printf("| %f | %f | %f |\n",mat_1[2][0],mat_1[2][1],mat_1[2][2]);
    printf("----------------------------------\n");                                                                            //print matrix
    BOARD_End();
    while (1);
}

