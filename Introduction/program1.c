#include<stdio.h>
#include<omp.h>

void pooh(double A[], int a){
    printf("%d\n",a);
}

int main(){
    double A[1000];
    omp_set_num_threads(4);

    //Each thread will execute the following block of code.
    #pragma omp parallel 
    {
        int ID = omp_get_thread_num();
        pooh(A,ID);
    }

    printf("All Done\n");
}