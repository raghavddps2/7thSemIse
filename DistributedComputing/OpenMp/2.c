#include<stdio.h>
#include<omp.h>

/*

    We are required to multiply a matrix by a vector.
    We will store this matrix in a 2D array.
    [[0,3,5],
    [5,5,2]]

    Vector is given as: --> We will store this in a 1D array.
    [
        3
        4
        3
    ]
*/

int main(){

    int noOfRows, noOfCols, vectorSize, i, j;

    printf("Enter the number of rows in the matrix:\t");
    scanf("%d",&noOfRows);
    printf("Enter the number of columns in the matrix:\t");
    scanf("%d",&noOfCols);
    printf("Enter the number of columns in the vector:\t");
    scanf("%d",&vectorSize);

    int matrix[noOfRows][noOfCols];
    int vector[vectorSize];

    if(noOfRows <=0 || noOfCols <= 0 || vectorSize <= 0 || noOfCols != vectorSize){
        printf("Invalid Input");
        return 0;
    }
    

    for(int i=0;i<noOfRows;i++){
        for(int j=0;j<noOfCols;j++){
            // printf("Enter the element:\t");
            // scanf("%d",&matrix[i][j]); 
            matrix[i][j] = i + j;
        }
    }

    for(int i=0;i<vectorSize;i++){
        // printf("Enter the element:\t");
        // scanf("%d",&vector[i]);
        vector[i] = i;
    }

    /*
        It is as simple as multiplying first row with entire first column
        0*3 + 3*4 + 5*3 = 0 + 12 + 15 = 27
        5*3 + 5*4 + 3*2 = 15 + 20 + 6 = 41
    */
   for(int i=0;i<noOfRows;i++){
        for(int j=0;j<noOfCols;j++){
            // printf("%d\t",matrix[i][j]);
        }
        // printf("\n");
    }

   int result[noOfRows];
   for(int i=0;i<noOfRows;i++){
       result[i] = 0;
   }

   /*
        This is the part of the code that needs to be parallelized.
   */

   double t1 = omp_get_wtime();

   omp_set_num_threads(4);
   #pragma omp parallel for private(j)
   for(int i=0;i<noOfRows;i++){
       for(int j=0;j<noOfCols;j++){
           result[i] += matrix[i][j]*vector[j];
       }
   }

    double t2 = omp_get_wtime();
    printf("The time required by the program is:\t%f",t2-t1);
    printf("\n");
    //We got an NX1 vector which we have stored in an array.
    for(int i=0;i<noOfRows;i++){
        printf("%d\t",result[i]);
    }
    printf("\n");

}