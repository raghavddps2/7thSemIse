/**
 * 
 * C program to multiply a matrix with a vector.
 * */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void main(){
    int numRows, numCols, vectorSize;
    omp_set_num_threads(4);
    printf("\n Enter the number of rows:\t");
    scanf("%d",&numRows);

    printf("\n Enter the number of columns:\t");
    scanf("%d",&numCols);

    printf("\n Enter the size of the vector:\t");
    scanf("%d",&vectorSize);

    if(numRows <=0 || numCols <= 0 || numRows != vectorSize){
        printf("\nInvalid dimensions!");
        exit(0);
    }

    //defining the matrix
    int matrix[numRows][numCols];
    int i=0,j=0;
    for(int i=0;i<numRows;i++){
        for(int j=0;j<numCols;j++){
            matrix[i][j] = i + j;
        }
    }

    int vector[vectorSize];
    for(int i=0;i<vectorSize;i++){
        vector[i] = i + 1;
    }

    printf("\n The original matrix is:\n");
    for(int i=0;i<numRows;i++){
        for(int j=0;j<numCols;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }    

    printf("\n The vector is: \n");
    for(int i=0;i<vectorSize;i++){
        printf("%d ",vector[i]);
    }
    printf("\n");

    int result[vectorSize]; //This contains the result.
    for(int i=0;i<vectorSize;i++){
        result[i] = 0;
    }
    //Now, we need to multiply the matrix with the vector.

    #pragma omp parallel for private(j)
    for(i=0;i<numRows;i++){
        printf("%d ",omp_get_thread_num());
        for(j=0;j<numCols;j++){
            result[i] = result[i] +  vector[j]*matrix[i][j];
        }   
    }

    //Printing the result.
    printf("\nThe multiplication of the matrix with the vector is:\n");
    for(int i=0;i<vectorSize;i++){
        printf("%d ",result[i]);
    }
    printf("\n\n");
}