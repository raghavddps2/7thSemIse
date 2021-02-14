#include<stdio.h>
#include<mpi.h>
#include<string.h>
void main(int argc, char *argv[]){

    char message[10];
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    //We need to learn broadcasting.
    //We are broadcasting from process 1
    if(rank == 0){
        strcpy(message,"Raghav"); //This will automatically appear in all the processes.
        //We are broadcasting it.
        MPI_Bcast(message,10,MPI_CHAR,0,MPI_COMM_WORLD);
    }
    else{
        //Is not received here - Issue - Check!!
        printf("\nMessage in process %d is %s\n",rank,message);
    }

    MPI_Finalize();
}