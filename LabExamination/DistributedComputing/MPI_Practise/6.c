/**
 * C program which searches integers between A and B for a value J such that F(J) = C, using the
 * MPI parallel programming environment.
 * */

#include<stdio.h>
#include<mpi.h>
#include<math.h>


int F(int i){
    return i*i;
}

int search(int a,int b,int c,int rank,int size){
    int j = -1;

    //a+rank, so that all processes does not check on all values.
    for(int i=a+rank;i<=b;i+=size){
        int fi = F(i);
        if(fi == c){
            j = i;
            break;
        }
    }
    return j;
}

void main(int argc,char *argv[]){

    int size,rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int a = 1;
    int b = 100000;
    int c = 900;

    if(rank == 0){
        printf("A = %d, B = %d, C = %d", a, b, c);
    }
    int j;
    double t1 = MPI_Wtime();
    j = search(a,b,c,rank,size);
    double t2 = MPI_Wtime();

    if(j != -1){
        printf("\nProcess %d found the value of J as %d in time %f\n",rank,j,t2-t1);
    }
    MPI_Finalize();
}