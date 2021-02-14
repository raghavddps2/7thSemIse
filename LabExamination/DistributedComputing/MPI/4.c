//C program which creates new communicators involving a subset of initial set of MPI processes in the default communicator MPI_COMM_WORLD
/**
 * 
 * 1. We have used the communicator as MPI_COMM_WORLD, and for simple applications this is sufficient,
 * 	  as we have a relatively small number of processes and we usually talk to one of them at a time
 * 	  or all of them at a time.
 * 
 * 2. When applications get bigger, this becomes impractical and we only want to talk to a few processes
 * 	  at once. So, we create new communicators to communicate with a subset of the original group of
 * 	  processes at once.
 * 
 * 3. MPI_Scatter - Distribute data from one process to another.
 * 	  MPI_Reduce - Data reduction on the processes
 * 
 * 4. MPI_Comm_split is one of the most common communicator creator function. And there are many others,
 * 	  MPI_Comm_dup is the most basic and creates a duplicated of a communicator.
 * 
 * 5. 	
 * */

#include<stdio.h>
#include<mpi.h>

void main(int argc, char* argv[]){

	int size,rank;
	MPI_Group groupId, evenGroupId, oddGroupId;
	MPI_Comm EVEN_Comm, ODD_Comm;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	MPI_Comm_group(MPI_COMM_WORLD,&groupId);

	// processors - 5, odd Processor - 1,3
	// processors - 5, even processors - 0,2,4
	int evenPSize = (size+1)/2;
	int oddPSize = (size)/2;

	int evenRanks[evenPSize];
	int oddRanks[oddPSize];

	//Assigning ranks
	int j = 0;
	for(int i=0;i<size;i+=2){
		evenRanks[j] = i;
		j = j + 1;
	}

	//creating the group
	MPI_Group_incl(groupId,evenPSize,evenRanks,&evenGroupId);
	//creating the communicator
	MPI_Comm_create(MPI_COMM_WORLD,evenGroupId,&EVEN_Comm);


	j = 0;
	for(int i=1;i<size;i+=2){
		oddRanks[j] = i;
		j += 1;
	}

	/**
	 * Now, we need to create 2 things.
	 * 
	 * 1. We need to create a group that includes only even ranks
	 * 2. We need to create a communicator for that group.
	 * */

	MPI_Group_incl(groupId,oddPSize,oddRanks,&oddGroupId);
	MPI_Comm_create(MPI_COMM_WORLD,oddGroupId,&ODD_Comm);


	int oddRank, evenRank;
	int evenSum, oddSum;
	int isOdd, isEven;

	//Simply we need to initialize ranks, 
	//meaning odd
	if(rank%2 != 0){
		MPI_Comm_rank(ODD_Comm,&oddRank);
		isEven = -1;
	}

	if(rank%2 == 0){
		MPI_Comm_rank(EVEN_Comm,&evenRank);
		isOdd = -1;
	}

	//reduce even
	if(isOdd != -1){
		MPI_Reduce(&rank,&oddSum,1,MPI_INT,MPI_SUM,0,ODD_Comm);
	}
	
	if(oddRank == 0){
		printf("\n\n Sum of processes in odd communicator: %d \t",oddSum);
		printf("\n\n Number of processes in odd communicator: %d\t",oddPSize);
	}

	//reduce odd
	if(isEven != -1){
		MPI_Reduce(&rank,&evenSum,1,MPI_INT,MPI_SUM,0,EVEN_Comm);
	}

	if(evenRank == 0){
		printf("\n\n Sum of processes in even communicator: %d\t ",evenSum);
		printf("\n\n Number of processes in Even Communicator: %d\t",evenPSize);
	}
	printf("\n");
	MPI_Finalize();
}