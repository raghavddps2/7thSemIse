/**
 *  Write MPI program to compute dot product of two vectors using block-striped partitioning with 
 * uniform data distribution.
 * */

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<string.h>
#define vectorSize 6

int main(int argc, char** argv){
    int rank,size;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int A[vectorSize] = {1,1,1,1,1,1}; //vector 1
    int B[vectorSize] = {2,2,2,2,2,2}; //vector 2
    int C[vectorSize],result;
    int vecSize = vectorSize;
    
    //Broadcasts a message from the process with rank "root" to all other processes of the communicator.
    MPI_Bcast(&vecSize,1,MPI_INT,0,MPI_COMM_WORLD);

    int scatterSize = vectorSize/size; //To basically check if uniform distribution is possible or not.
    int buffA[scatterSize], buffB[scatterSize], buffC;


    //Makes scatters from the given array.
    MPI_Scatter(A,scatterSize,MPI_INT,buffA,scatterSize,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(B,scatterSize,MPI_INT,buffB,scatterSize,MPI_INT,0,MPI_COMM_WORLD);

    // Forms the bufferResult and then we Reduce it using thh sum operator.
    for(int i=0;i<scatterSize;i++){
        buffC += buffA[i]*buffB[i];
    }   

    // Here, we use the MPI_SUM operator to acctually sum over all the values.
    MPI_Reduce(&buffC,&result,1,MPI_REAL,MPI_SUM,0,MPI_COMM_WORLD);

    //We are basically looking at the process with rank 0
    if(rank == 0){
            printf("Dot product of two vectors is %d calculated by %d processes\n",result,size);
    }

    MPI_Finalize();
    return 0;
}

