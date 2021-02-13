//C program which creates new communicators involving a subset of initial set of MPI processes in the default communicator MPILD
	#include<stdio.h>
	#include "mpi.h"
	#include<stdlib.h>
	
	void main(int argc, char **argv)
	{
	    MPI_Group groupId, evenGroupId, oddGroupId;
	    MPI_Comm EVEN_Comm, ODD_Comm;
	    
	    int rank, size;
	
	    MPI_Init(&argc, &argv);
	    MPI_Comm_size(MPI_COMM_WORLD, &size);
	    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	    
	
	    MPI_Comm_group(MPI_COMM_WORLD, &groupId);
	
	    int oddPSize = size / 2;
	    int evenPSize = (size + 1) / 2;
	    int evenRanks[evenPSize], oddRanks[oddPSize];
	
	    int j = 0;
	    for(int i = 0; i < size; i += 2)
	    {
	        evenRanks[j++] = i;
	        
	    }
	
	    j = 0;
	    for(int i = 1; i < size; i += 2)
	    {
	        oddRanks[j++] = i;
	        
	    }
	
	    MPI_Group_incl(groupId, evenPSize, evenRanks, &evenGroupId); //creating a group of even ranks
	    MPI_Comm_create(MPI_COMM_WORLD, evenGroupId, &EVEN_Comm); //creating a new communicator consisting of only even processes
	
	    MPI_Group_incl(groupId, oddPSize, oddRanks, &oddGroupId); //creating a group of odd ranks
	    MPI_Comm_create(MPI_COMM_WORLD, oddGroupId, &ODD_Comm); //creating a new communicator consisting of only odd processes
	        
	    int oddrank,evenrank;
	    int evensum, oddsum;
	    int isodd, iseven;
	    
	    if(rank %2 != 0)
	    {
	    	MPI_Comm_rank(ODD_Comm, &oddrank);
	    	iseven = -1;
	    }
	   
	    if(rank % 2 == 0)
	    {
	    	MPI_Comm_rank(EVEN_Comm, &evenrank);
	    	isodd = -1;
	    }
	    
	    if(isodd != -1)
	    	MPI_Reduce(&rank, &oddsum, 1, MPI_INT, MPI_SUM, 0, ODD_Comm);
	    if(iseven != -1)
	    	MPI_Reduce(&rank, &evensum, 1, MPI_INT, MPI_SUM, 0, EVEN_Comm);
	    	
	    if(oddrank == 0)
	    {
	    	printf("\nNo. of processes in odd communicator:%d\n", oddPSize);
	    	printf("Sum of odd ranks:%d\n", oddsum);
	    }
	    	
	    if(evenrank == 0)
	    {
	    	printf("\nNo. of processes in even communicator:%d\n", evenPSize);
	    	printf("Sum of even ranks:%d\n", evensum);
	    }
	    
	    MPI_Finalize();
	}
	