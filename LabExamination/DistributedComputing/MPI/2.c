/**
 * Write  MPI  program  to  compute  dot  product  of  two  vectors using 
 * block-striped partitioning with uniform data distribution
 * */

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#define vectorSize 6
int main(int argc, char** argv){

    int A[vectorSize] = {3,5,1,2,1,3};
    int B[vectorSize] = {2,2,2,2,2,2};
    int rank,numProcs;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numProcs);

    if(vectorSize%numProcs != 0){
        printf("No even distribution!");
        exit(0);
    }

    int scatterSize = vectorSize/numProcs;
    int buffA[scatterSize], buffB[scatterSize];
    int result;
    int buffC = 0; //IMP - Need to initialize with 0
    int vecSize = vectorSize;

    //Broadcasting to various processes
    MPI_Bcast(&vecSize,1,MPI_INT,0,MPI_COMM_WORLD);

    //Scattering into various processes - The computations!!
    MPI_Scatter(A,scatterSize,MPI_INT,buffA,scatterSize,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(B,scatterSize,MPI_INT,buffB,scatterSize,MPI_INT,0,MPI_COMM_WORLD);

    //This will compute the Dot product
    for(int i=0;i<scatterSize;i++){
        buffC += buffA[i]*buffB[i];
        printf("%d %d %d\n",buffA[i],buffB[i],buffC);
    }
    printf("%d\n",buffC);

    //Reducing the output of buffC to a single value result.
    MPI_Reduce(&buffC,&result,1,MPI_REAL,MPI_SUM,0,MPI_COMM_WORLD);


    //Finally print
    if(rank == 0){
        printf("The dot product of two vectors is %d and is calculated by %d processes", result,numProcs);
    }
}
