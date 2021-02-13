#include<stdio.h>
#include<string.h>
#include<mpi.h>
#define BUFFER_SIZE 32

int main(int argc, char* argv[]){

    int rank,numProcs;
    int root = 3;

    int tag = 0; //whatever the message tag is (basically an identifier for message)
    char message[BUFFER_SIZE]; //defining the message
    
    //general initializations
    MPI_Init(&argc,&argv); 
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numProcs);

    //Whenever we have rank 3, we just send and others we receive.
    if(rank == 3){
        strcpy(message,"Hello");
        for(int temp = 0;temp<numProcs;temp++){
            if(temp != 3){
                MPI_Send(message,BUFFER_SIZE,MPI_CHAR,temp,tag,MPI_COMM_WORLD);
            }   
        }
    }
    //receving noww!!
    else{
        MPI_Recv(message,BUFFER_SIZE,MPI_CHAR,root,tag,MPI_COMM_WORLD,&status);
        printf("%s received to a process with rank %d from a process with rank %d",message,rank,root);
    }

}
