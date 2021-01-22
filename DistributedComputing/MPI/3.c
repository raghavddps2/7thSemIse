/**
 * Write an MPI program that computes the value of PI using the Monto-Carlo program.
 * Before going ahead, it is very important to understand the monto-carlo algorithm only.
 * 
 * Consider we make a unit circle and enclose it with a square. The length of the side of square will be 
 * 2 units.
 * 
 * Area of one quater of circle = (PI*1*1)/4
 * Area of one quater of square = (2*2)/4
 * 
 * So, the ratio of 2 comes out to be = PI/4 = lambda
 * 
 * Now, lets split up points and the lambda is eqial to number of points lying inside the 
 * circle and not square quater.
 * */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<mpi.h>
#include<math.h>

int main(int argv, char** argc){

    int rank,size;
    int count = 0;
    MPI_Init(&argv,&argc);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    double timeelapsed;
    long int iterations = 10000000;
    int processIterations = iterations/size; //Telling number of iterators each procesor has to do.

    double start = MPI_Wtime();


        //Here, we will perform the amin step of the monto carlo algorithm
        for(int i=0;i<processIterations;i++){
            double x = ((double)(rand()))/RAND_MAX;
            double y = ((double)(rand()))/RAND_MAX;

            if(sqrt(x*x+y*y) <= 1){
                count++;
            }
        }

    double end = MPI_Wtime();
    double totalTime = end-start;
    int result;
    //Now, we need to use the MPI_reduce operator to sum all this individual counts.
    MPI_Reduce(&count,&result,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Reduce(&totalTime,&timeelapsed,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);

    //Now, we will print the output only when rank is 0
    if(rank == 0){
        double PI = 4*result/(double)iterations;
        printf("\nValue of PI: %f",PI);
        printf("\nActual value of PI: %F",M_PI);
        printf("\nError in value: %f",M_PI-PI);
        printf("\nTotal time taken: %f\n",timeelapsed);
    }
    MPI_Finalize();
}