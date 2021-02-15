#include<stdio.h>
#include<omp.h>

void main(){
    int n;
    long fact1=1,fact2=1;
    printf("\n Enter the value of n:\t");
    scanf("%d",&n);

    #pragma omp parallel for reduction(*:fact1)
    for(int i=1;i<=n;i++){
        fact1 = fact1 * i;
    }

    printf("\nWhen first private is not used");
    printf("\nThe factorial of %d is %ld",n,fact1);

    #pragma omp parallel for firstprivate(fact2)
    for(int i=1;i<=n;i++){
        fact2 = fact2 * i;
    }

    printf("\nWhen first private is used");
    printf("\nThe factorial of %d is %ld",n,fact2);
    printf("\n");
}