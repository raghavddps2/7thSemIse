/**
 *  C program which creates new communicators involving a subset of initial set of MPI processes 
 *  in the default communicator MPI_COMM_WORLD
 * 
 **/


#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc,char** argv){

    int rank,size;
    // We form the MPI_Group for both the even and the odd processes too.
    MPI_Group groupId,evenGroupId,oddGroupId;
    // We form the MPI_Communicator objects for both Even and Odd processes.
    MPI_Comm EVEN_Comm, ODD_Comm;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_group(MPI_COMM_WORLD,&groupId);


    int oddPSize = (size)/2;
    int evenPSize = (size+1)/2;

    //We form the array for the ranks.
    int evenRanks[evenPSize], oddRanks[oddPSize];
    int j = 0;
    for(int i=0;i<size;i+=2){
        evenRanks[j] = i;
        j = j + 1;
    }

    j = 0;
    for(int i=1;i<size;i+=2){
        oddRanks[j] = i;
        j = j + 1;
    }

    //We need to create group of even ranks and create the communicator.
    MPI_Group_incl(groupId,evenPSize,evenRanks,&evenGroupId);
    MPI_Comm_create(MPI_COMM_WORLD,evenGroupId,&EVEN_Comm);

    //We need to create groups of odd rank and create the communicator.
    MPI_Group_incl(groupId,oddPSize,oddRanks,&oddGroupId);
    MPI_Comm_create(MPI_COMM_WORLD,oddGroupId,&ODD_Comm);

    int oddRank,evenRank;
    int isodd,iseven;
    int oddSum,evenSum;
    //Assigning the groups ransk to the MPI_Comm_rank method.
    if(rank%2 != 0){
        MPI_Comm_rank(ODD_Comm,&oddRank);
        iseven = -1;
    }

    if(rank%2 == 0){
        MPI_Comm_rank(EVEN_Comm,&evenRank);
        isodd = -1;
    }

    //Now, whenever they arenot -1, we can simply use the reduce operator.
    if(isodd != -1){
        MPI_Reduce(&rank,&oddSum,1,MPI_INT,MPI_SUM,0,ODD_Comm);
    }
    if(iseven != -1){
        MPI_Reduce(&rank,&evenSum,1,MPI_INT,MPI_SUM,0,EVEN_Comm);
    }

    //Now simply whenever we will have rank 0, we will print.
    if(oddRank == 0){
        printf("\nNo of processes in odd communicator:%d\n",oddPSize);
        printf("\n Sum of odd ranks:%d\n",oddSum);
    }

    if(evenRank == 0){
        printf("\nNo of processes in even communicator:%d\n",evenPSize);
        printf("\nSum of even ranks:%d\n",evenSum);
    }

    MPI_Finalize();

}
