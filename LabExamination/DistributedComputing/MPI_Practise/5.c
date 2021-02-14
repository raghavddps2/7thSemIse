/**
 * Matrix multiplication using the Self scheduling algorithm.
 * */

#include<stdio.h>
#include<mpi.h>
#define BUFFER_SIZE sizeof(int)*4

void main(int agrc,char *argv[]){

    //We define the 3 matrices.
    int A[2][2] = {{1,2},{3,4}};
    int B[2][2] = {{0,1},{1,0}};
    int C[2][2] = {{0,0},{0,0}};

    int rank,size;

    MPI_Init(&agrc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank == 0){
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                C[i][j] = 0;
                for(int k=0;k<2;k++){
                    C[i][j] += A[i][k]*B[k][j];
                }
            }
        }
        //Now,we will send to other process.
        MPI_Send(&C,BUFFER_SIZE,MPI_INT,1,0,MPI_COMM_WORLD);
    }
    else if(rank == 1){
        int ans[2][2];
        MPI_Status status;
        MPI_Recv(&C,BUFFER_SIZE,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                printf("%d ",C[i][j]);
            }
            printf("\n");
        }
    }
    else{
        //do notthing!
    }
    MPI_Finalize();
}