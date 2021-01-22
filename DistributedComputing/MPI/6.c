/**
 * C program which searches integers between A and B for a value J such that F(J) = C, using
 * the MPI Parallel processing environment.
 * */

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<time.h>

int F(int i){
    return i*i;
}

int search(int a,int b,int c,int rank,int size){
    int j = -1;
    for(int i=a+rank;i<=b;i+=size){
        int fi = F(i);
        //Simply when we find it to be equal, we break and then finally return j.
        if(fi == c){
            j = i;
            break;
        }
    }
    return j;
}

int main(int argc, char** argv){

    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    //We need to fing the value J such that F(J) = c, between a and b
    int a = 1;
    int b = 10000000;
    int c = 81; //preferably this should be a perfect square for the Function F to be of any value.
    int j;
    if(rank == 0){
        printf("\nA=%d,B=%d,C=%d",a,b,c);
    }
    double startTime = MPI_Wtime();
    j = search(a,b,c,rank,size);
    double endTime = MPI_Wtime();   
    double time = endTime-startTime;

    //If we have j != -1, we found it.
    if(j != -1){
        printf("\nProcess %d found",rank);
        printf("\nJ=%d",j);
        printf("\nVerify F(j)=%d",F(j));
        printf("\nTime Taken:%lf\n",time);
    }
    MPI_Finalize();
}


