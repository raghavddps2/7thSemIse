/**
 * Write an MPI program to compute the dot product of two vectors using block striped partitioning 
 * with uniform data distribution.
 * 
 * Steps
 * 
 * 1. MPI_Bcast the vectorSize.
 * 2. Scatter the two vectors over processes.
 * 3. Calculate the sum of the blocks
 * 4. Combine all using MPI_Reduce.
 * */

#include<stdio.h>
#include<mpi.h>
#define vectorSize 6
void main(int argc, char *argv[]){

    int size,rank;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int A[vectorSize] = {1,2,3,4,5,6};
    int B[vectorSize] = {1,2,3,4,5,6};
    int vecSize = vectorSize;
    MPI_Bcast(&vecSize,1,MPI_INT,0,MPI_COMM_WORLD);
    //we calculate the scatter size as vectorSize/size
    int scatterSize = vectorSize/size;  

    int buffA[scatterSize];
    int buffB[scatterSize];

    //We now need to scatter the input
    MPI_Scatter(A,scatterSize,MPI_INT,buffA,scatterSize,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(B,scatterSize,MPI_INT,buffB,scatterSize,MPI_INT,0,MPI_COMM_WORLD);

    int mySum = 0;
    int totalSum = 0;
    //Now, all we need to do is to combine.
    for(int i=0;i<scatterSize;i++){
        mySum += buffA[i]*buffB[i];
    }

    //Now, we can reduce.
    //reduced at the root.
    MPI_Reduce(&mySum,&totalSum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank == 0){
        printf("The result of the multiplication of 2 vectors is %d\n",totalSum);
    }
    MPI_Finalize();
}
