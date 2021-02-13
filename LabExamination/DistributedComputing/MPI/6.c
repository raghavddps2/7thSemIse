/**
 * C program which searches integers between A and B for a value J
 * such that F(J) = C, using the MPI parallel programming environment
 * */

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int F(int i){
    return i*i;
}

int search(int a,int b, int c, int rank, int size){
    int j = -1;
    // i = 1+ rank and i<=b and i+= size
    for(int i=a+rank;i<=b;i+=size){
        int fi = F(i);
        if(fi == c){
            j = i;
            break;
        }
    }
    return j;
}

int main(int argc,char** argv){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    //we need to find a value of J, such that F(J) = C , between a and b
    //Just initializing stuff
    int a = 1;
    int b = 10000000;
    int c = 81;
    int j;
    if(rank == 0){
        printf("\nA=%d",a);
        printf("\nB=%d",b);
        printf("\nC=%d",c);
    }
    //searching
    j = search(a,b,c,rank,size);
    //printing result
    if(j != -1){
        printf("Process %d found",rank);
        printf("\nJ=%d\n",j);
    }
    MPI_Finalize();
}