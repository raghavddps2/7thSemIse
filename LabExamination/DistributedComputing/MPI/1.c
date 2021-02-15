/**
 * Program for communication among two processes.
 * 
 * */
#include<stdio.h>
#include<mpi.h>
#include<string.h>
#define BUFFER_SIZE 32
void main(int argc, char *argv[]){
    
    char message[BUFFER_SIZE];
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    //Sending message from the master process to all the other processes.
    if(rank == 0){
        strcpy(message,"Raghav is a boy");

        for(int i=0;i<size;i++){
            if(i != 0){
                MPI_Send(message,32,MPI_CHAR,i,0,MPI_COMM_WORLD);
            }
        }
    }
    else{
        //Receving it in all the other processes.
        char message2[BUFFER_SIZE];
        MPI_Status status;
        MPI_Recv(message2,BUFFER_SIZE,MPI_CHAR,0,0,MPI_COMM_WORLD,&status);
        printf("\n Message received from process 0 in process %d: %s\n",rank,message2);
    }
}

