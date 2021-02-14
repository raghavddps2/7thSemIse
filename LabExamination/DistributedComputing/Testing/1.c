
#include<stdio.h>
#include<mpi.h>
#include<string.h>
/**
 * This snippet simply teels so manyy things.
 * Based on the value we provide with -np, we get the size or the number of processes.
 * Then rank for each process is an integer defining the process.
 * */
void main(int argc, char *argv[]){

    int rank,size;
    char message[10];
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank == 0){
        printf("\nNo of processes: %d",size); 
    }
    printf("\nRank of process: %d\n",rank);

    //learning how we communicate from one process to another.
    if(rank == 0){
        //basically process 0 is sending the data.

        strcpy(message,"Raghav");

        //Now, this is sending data to process 1
        for(int i=1;i<size;i++){
            MPI_Send(message,10,MPI_CHAR,i,0,MPI_COMM_WORLD);
        }
    }
    else{
        //process 1 is receving the data sent.
        char message2[10];
        MPI_Status status;
        //receving the data here in another variable.
        MPI_Recv(message2,10,MPI_CHAR,0,0,MPI_COMM_WORLD,&status);
        printf("\n%s recevied at process %d\n",message2,rank);
    }
    MPI_Finalize();
}