// /**
//  * Write a program to display how the firstprivate clause works
//  * 
//  *  Private(var) clause
//  *      * This creates a local copy of var for each thread.
//  *      * The value is uninitialized
//  *      * The roiginal is undefined at the end
//  *      
//  *      Each thread gets its own var which are however not initialized.
//  *      Regardsless of the initialization, var is undefined at the end of the parallel region
//  * 
//  * First Private Clause
//  *  
//  *      First Private is a special case of private
//  *      Initializes each private copy with the corresponding value from the master thread.
//  *      Regardsless of the initialization, var is undefined at the end of parallel region.
//  * 
//  * Reduction
//  *      
//  *      This specifies that one or more variables that are private to each thread are the subject 
//  *      of a reduction operation at the end of the parallel region
//  * */

// #include<stdio.h>
// #include<omp.h>
// int main(){
//     omp_set_num_threads(8);

//     int n;
//     printf("\n Enter the number n:\t");
//     scanf("%d",&n);

//     int fact1 = 1;
//     int fact2 = 1;
//     int i = 1;
//     #pragma omp parallel for reduction(*:fact1)
//     for(i=1;i<=n;i++){
//         fact1 = fact1*i;
//     }

//     #pragma omp paralllel for firstprivate(fact2)
//     for(i=1;i<=n;i++){
//         fact2 = fact2 * i;
//     }
//     printf("%d",fact2);
// }
//Factorial
	
	#include<omp.h>
	#include<stdio.h>
	
	void main() 
	{
		int fact1 = 1,fact2 = 1;
		int a,i;
		
		printf("Enter a number to check its factorial\n");
		scanf("%d",&a);
		
		#pragma omp parallel for firstprivate(a) num_threads(8)
		for(i = 2; i<=a; i++) 
		{
			fact1 = fact1 * i;
		}
	
		printf("When first private is not used\n");
		printf("factorial of %d is %d \n",a,fact1);
		
		#pragma omp parallel for firstprivate(a,fact2) num_threads(8)
		for(i = 2; i<=a; i++) 
		{
			fact2 = fact2 * i;
		}
	
		printf("When first private is used\n");
		printf("factorial of %d is %d \n",a,fact2);
	}