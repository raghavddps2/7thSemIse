/**
 * MPI program to calculate the value of PI using the MONTO CARLO program.
 * 
 * 1. Monto Carlo algorithm is very easy
 * 2. Area of square = 4*R*R
 * 3. Area of Circle = PI*R*R
 * 4. Area of circle/area of square = Number of points lyting in circle by number in a square.
 * 5. Calculate PI by multiplying this by 4.
 * */

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

void main(int argc,char *argv[]){

    MPI_Init(&argc,&argv);
    int size,rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int numberOfIterations = 100000000;
    int numProIter = numberOfIterations/size;
    int count = 0;
    int ans = 0;
    int totalCount = 0;
    srand(time(NULL)+rank);
    int i = 0;

    for(i=0;i<numProIter;i++){
        double x = (double)random()/RAND_MAX;
        double y = (double)random()/RAND_MAX;
        printf("%f %f",x,y);
        //quadrant splitting logic used here for the distance.
        if((sqrt((x*x)+(y*y))) <= 1){
            count = count + 1;
        }
    }
    
    //We calculate the totalCount of the numbers and the number of iterations.
    MPI_Reduce(&numProIter,&ans,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Reduce(&count,&totalCount,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank == 0){
        double expectedPI = ((double)totalCount/(double)ans)*4.0;
        printf("The calculated value of PI is %f", expectedPI);
    }

    MPI_Finalize();
}

