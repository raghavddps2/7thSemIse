#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void merge(int arr[], int x1, int y1, int x2, int y2){

    int i = x1; //This initialized with start array values
    int j = x2;
    int k = 0;
    int temp[y2];
    while(i <= y1 && j <= y2){
        if(arr[i] < arr[j]){
            temp[k] = arr[i];
            i = i + 1; 
        }
        else{
            temp[k] = arr[j];
            j = j + 1;
        }
        k = k + 1;
    }

    //Now, check if any of it is empty
    while(i <= y1){
        temp[k] = arr[i];
        k = k + 1;
        i = i + 1;
    }

    while(j <= y2){
        temp[k] = arr[j];
        k = k + 1;
        j = j + 1;
    }
    j = 0;
    for(i=x1;i<=y2;i++){
        arr[i] = temp[j];
        j = j + 1;
    }

}

void mergeSort(int arr[], int low, int high){
    omp_set_num_threads(8);
    //if low < high, we enter and split the array
    if(low < high){
        int mid = low + (high-low)/2;
        #pragma omp parallel sections
        {

            #pragma omp section
            {
                printf("\nProcess handling left recursion is %d ", omp_get_thread_num());
                mergeSort(arr,low,mid); //Okay
            }

            #pragma omp section
            {
                printf("\nProcess handling right recursion is %d ", omp_get_thread_num());
                mergeSort(arr,mid+1,high); 
            }
        }
        merge(arr,low,mid,mid+1,high); //Okay
    }
}

void  main(){
    int n;
    
    //Taking the input n from the user - Okay
    printf("\nEnter the number of elements:\t");
    scanf("%d",&n);

    int arr[n];

    //Taking the random integers and putting in the array - Okay
    for(int i=0;i<n;i++){
        arr[i] = rand()%100;
    }

    //Printing the original array - Okay
    printf("The original array is: \n");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }

    mergeSort(arr,0,n-1); //- Okay

    printf("\n The sorted array is:\n"); // - Okay
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
