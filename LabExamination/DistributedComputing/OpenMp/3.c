#include<stdio.h>
#include<math.h>
#define PI 3.1415
int primes[1000];
double sines[1000];

void calculatePrimes(int n){

    int i = 2;
    int count = 0;
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

void calculateSines(int n){

    // 180 degree = PI radians
    // i degreees = (PI/180)*i
    for(int i=0;i<n;i++){
        sines[i] = sin((PI/180)*i);
    }
}

void main(){

    int nPrimes;
    int nSines;

    printf("\n Enter the number of primes you want:\t");
    scanf("%d",&nPrimes);
    printf("\n Enter the number of sines you want:\t");
    scanf("%d",&nSines);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            calculatePrimes(nPrimes);
        }
        #pragma omp section 
        {
            calculateSines(nSines);
        }
    }

    

    //Printing primes
    printf("\n The primes are as follows:\t");
    for(int i=0;i<nPrimes;i++){
        printf("%d ",primes[i]);
    }

    //Printing the sines.
    printf("\n The sines are as follows:\t");
    for(int i=0;i<nSines;i++){
        printf("%f ",sines[i]);
    }
    printf("\n");
}