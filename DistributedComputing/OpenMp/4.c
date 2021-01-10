/*
    Write a program to show how the private clause works.

    Private clause
        private(var) creates a local copy of var for each thread
            - The value is uninitialized.
            - Private copy is not storage associated with the children
            - The original is undefined at the end

        Each thread gets its own var which are however not initialized.
        Regardless of initialization, var is undefined at the end of the parallel region.

    First Private clause

        FirstPrivate is a special case of private
            - Initializes each private copy with the corresponding value from the master thread.
            - Regardless of the initialization, var is undefnied at the end of the parallel region.

*/

#include<stdio.h>
#include<omp.h>

int main(){

    int fact1 = 1;
    int fact2  = 1;

    int input,i;

    printf("\n Enter the number to check its factorial:\t");
    scanf("%d",&input);

    //This implies, a is initialized with the outside value.
    #pragma omp parallel for firstprivate(input)
    for(i=2;i<=input;i++){
        fact1 = fact1 * i;
    }

    printf("\nWhen first private is not used:\n");
    printf("Factorial of %d is %d",input,fact1);

    // The initial value of 1 should be retained.
    #pragma omp parallel for firstprivate(input,fact2)
    for(i=2;i<=input;i++){
        fact2 = fact2 * i;
    }

    printf("\nWhen first private is used:\n");
    printf("Factorial of %d is %d\n",input,fact2);

}
