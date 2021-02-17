/**
 * Write A C program which creates new communicators involving a subset of initial set of MPI 
 * processes in the default communicator MPI_COMM_WORLD
 * */

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

void main(int argc,char *argv[]) {
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    MPI_Comm odd_comm_id, even_comm_id;
    MPI_Group world_group_id,odd_group_id,even_group_id;

    if(rank == 0){
        printf("\nCommunicator MPI: Master process");
        printf("\nThe number of processes are %d ",size);
    }

    MPI_Comm_group(MPI_COMM_WORLD,&world_group_id);

    int even_p,odd_p;
    int even_id,odd_id;
    int even_id_sum, odd_id_sum;
    
    even_p = (size+1)/2;
    odd_p = (size)/2;

    int even_ranks[even_p];
    int odd_ranks[odd_p];

    int j = 0;
    int k = 0;
    for(j=0;j<size;j+=2){
        even_ranks[k] = j;
        k = k + 1;
    }

    j = 0;
    k = 0;
    for(j=1;j<size;j+=2){
        odd_ranks[k] = j;
        k = k + 1;
    }

    //create group and communicator.
    MPI_Group_incl(world_group_id,even_p,even_ranks,&even_group_id);
    MPI_Comm_create(MPI_COMM_WORLD,even_group_id,&even_comm_id);

    MPI_Group_incl(world_group_id,odd_p,odd_ranks,&odd_group_id);
    MPI_Comm_create(MPI_COMM_WORLD,odd_group_id,&odd_comm_id);

    //odd rank
    if(rank%2 != 0){
        MPI_Comm_rank(odd_comm_id,&odd_id);
        even_id = -1;
    }

    if(rank%2 == 0){
        MPI_Comm_rank(even_comm_id,&even_id);
        odd_id = -1;
    }

    if(odd_id != -1){
        MPI_Reduce(&rank,&odd_id_sum,1,MPI_INT,MPI_SUM,0,odd_comm_id);
    }

    if(even_id != -1){
        MPI_Reduce(&rank,&even_id_sum,1,MPI_INT,MPI_SUM,0,even_comm_id);
    }

    if(even_id == 0){
        printf("\nNumber of processes in the even communicator: %d\n",even_p);
        printf("\nSum of global id's in even communicator:%d\n",even_id_sum);
    }
    if(odd_id == 0){
        printf("\nNumber of processes in the odd communicator: %d\n",odd_p);
        printf("\nSum of global id's in odd communicator:%d\n",odd_id_sum);
    }
    MPI_Finalize();
}