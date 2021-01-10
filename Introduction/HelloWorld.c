#include<stdio.h>
#include<omp.h>
int main(){

    /*
        #include<omp.h> -> OpenMP include file.
        #pragma omp parallel --> This will take default number of threads.
        #pragma omp parallel num_threads(4) -> This will have specifically 4 threads.
    */

    # pragma omp parallel num_threads(4)
    {
    int id = omp_get_thread_num();
    printf("Hello World %d \n",id);
    }
}