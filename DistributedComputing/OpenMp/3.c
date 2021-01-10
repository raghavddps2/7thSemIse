#include<stdio.h>
#include<omp.h>
#include<math.h>
#define PI 3.14159265359


int primes[1000];
double sines[1000];

void generatePrimes(int n){
    int count = 0;
    int i = 2;

    while(count < n){
        int prime = 1;
        for(int j=2;j<=i/2;j++){
            if(i%j == 0){
                prime = 0;
                break;
            }
        }

        if(prime == 1){
            primes[count] = i;
            count = count + 1;
        }

        i = i + 1;
    }
}

/*
    So, i will generate for angle 0* to 100*
*/

void generateSines(int n){
    for(int i=0;i<n;i++){
        //180 degrees = PI radians.
        //i degree = (PI/180)*i
        sines[i] = sin((PI/180.0)*i);
    }
}

int main(){
    int n;
    printf("Enter the number of values you want:\t");
    scanf("%d",&n);
    //sections - Houses section
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            generatePrimes(n);
            printf("Printing primes");
            for(int i=0;i<n;i++){
                printf("\n%d",primes[i]);
            }
        }

        #pragma omp section
        {
            generateSines(n);
            printf("Printing sines");
            for(int i=0;i<n;i++){
                printf("\n%f",sines[i]);
            }
        }
    }
}