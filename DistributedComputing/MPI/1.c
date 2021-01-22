/**
 * Write a program for communication among two processes.
 * 
 **/
#include<stdio.h>
#include<mpi.h>
#include<string.h>

int main(int argc,char **argv){
    int rank,size;
    int stringSize;
    char* message;

    // This function is basically initializes the MPI environment. It takes the addresses of the 
    //command line arguments passed.
    MPI_Init(&argc,&argv);

    // This function returns the process id of the processor tthat called the function. 
    // The function takes in the MPI environment and memory address of an Integer variable.
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);


    //THis function returns the total size of the environment via quanity of processors.
    // The function takes in the MPI environment and memory address of an Integer variable.
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank == 0){
        message = "Hello from the master process";
        stringSize = strlen(message);

        //Sends the message for the receiver process
        //MPI_Send(message,count,datatype,receiver,sender,MPI_ENV)
        MPI_Send(message,stringSize,MPI_CHAR,1,0,MPI_COMM_WORLD);
    }
    else{

        //This function receives the message.
        MPI_Recv(message,stringSize,MPI_CHAR,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("Message from the master received by slave: %s\n",message);
    }

    //This function cleans up the Mpi environment and ends MPI Communication.
    MPI_Finalize();
    return 0;
}

