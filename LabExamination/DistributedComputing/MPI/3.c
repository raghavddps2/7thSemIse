/**
 * Write  MPI  program  that  computes  the  value  of  PI  using  Monto-Carlo Algorithm
 * */



#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
void main(int argc, char** argv){

    int rank,numProcs;
    MPI_Init(&argc,&argv);

    //Normal initialization
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numProcs);

    //Specifying iterations
    long int totalIter = 10000000;

    //specyfying the seed
    long int seed = time(NULL);

    //defining number of iterations per process
    int processIter = totalIter/numProcs;
    srand(seed + rank);
    int count = 0;
    int result = 0;
    for(int i=0;i<processIter;i++){
        double x = (double)(rand())/RAND_MAX;
        double y = (double)(rand())/RAND_MAX;

        if(sqrt(x*x + y*y) <= 1){
            count = count + 1;
        }
    }

    //combining the result
    MPI_Reduce(&count,&result,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank == 0){
        double pi = numProcs*result/(double)processIter;
        printf("\nActual value; %f",M_PI);
        printf("\nCalculated value: %f",pi);
        printf("\nError: %f",M_PI-pi);
    }
}