#include<stdio.h>
#include<mpi.h>

void main(int argc, char* argv[]){

    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);


    MPI_Comm odd_comm_id,even_comm_id;
    MPI_Group world_group_id,even_group_id,odd_group_id;

    MPI_Comm_group(MPI_COMM_WORLD,&world_group_id);

    int oddP = size/2;
    int evenP = (size+1)/2;

    int oddRanks[oddP];
    int evenRanks[evenP];

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

    int oddId,evenId;
    int totalOddSum,totalEvenSum;
    MPI_Group_incl(world_group_id,oddP,oddRanks,&odd_group_id);
    MPI_Comm_create(MPI_COMM_WORLD,odd_group_id,&odd_comm_id);

    MPI_Group_incl(world_group_id,evenP,evenRanks,&even_group_id);
    MPI_Comm_create(MPI_COMM_WORLD,even_group_id,&even_comm_id);

    //meaning odd
    if(rank%2 != 0){
        MPI_Comm_rank(odd_comm_id,&oddId);
        evenId = -1;
    }

    //meaning even
    if(rank%2 == 0){
        MPI_Comm_rank(even_comm_id,&evenId);
        oddId = -1;
    }

    if(oddId != -1){
        MPI_Reduce(&rank,&totalOddSum,1,MPI_INT,MPI_SUM,0,odd_comm_id);
    }

    if(evenId != -1){
        MPI_Reduce(&rank,&totalEvenSum,1,MPI_INT,MPI_SUM,0,even_comm_id);
    }

    if(oddId == 0){
        printf("\nNumber of processes in odd communicator: %d\n",oddP);
        printf("\nSum of ranks in odd communicator: %d\n",totalOddSum);
    }
    if(evenId == 0){
        printf("\nNumber of processes in even communicator: %d\n",evenP);
        printf("\nSum of ranks in even communicator: %d\n",totalEvenSum);
    }

    MPI_Finalize();

}