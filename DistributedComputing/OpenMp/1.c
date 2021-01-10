#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

/*
    This is the function responsible for merge.
*/
void merge(int a[],int x1,int y1,int x2,int y2){
    int p = x1;
    int q = x2;
    int k=0;
    int temp[100000];
    int i,j;

    // Hwere, we are just doing the merge into a new array
    while(p <= y1 && q <= y2){
        if(a[p] < a[q]){
            temp[k++] = a[p];
            p = p + 1;
        }
        else{
            temp[k++] = a[q];
            q = q + 1;
        }
    }

    //Now we will place the remaianing elements into temp

    while(p <= y1){
        temp[k++] = a[p++];
    }
    while(q <= y2){
        temp[k++] = a[q++];
    }

    //We will start substituting from x1 and go till y2, the last element of the second function call.
    for(i=x1,j=0;i<=y2;i++,j++){
        a[i] = temp[j];
    }
}

/*
    Here we have the merge sort function that works on the input sent.
*/
void mergeSort(int arr[],int p, int q){
    int mid = 0;
    if(p < q){
        mid = (p+q)/2;

        // This basically starts a parallel code with section clause (Please note sections)
        #pragma omp parallel sections
        {   
            //This one will run under a section and same for the next one. (section 1)
            #pragma omp section
            {   
                // printf("\nThread handling left recursion is %d",omp_get_thread_num());
                mergeSort(arr,p,mid);
            }

            #pragma omp section //(section 2)
            {
                // printf("\nThread handling right recursion is %d",omp_get_thread_num());
                mergeSort(arr,mid+1,q);
            }
        }
        merge(arr,p,mid,mid+1,q);
    }
}

int main(){
    omp_set_num_threads(4);
    int n;
    printf("Enter the number of elements:\t");
    scanf("%d",&n);

    int arr[n];
    ///randomly generating the values.
    for(int i=0;i<n;i++){
        arr[i] = rand()%100;
    }

    // printf("The unsorted array is:\n");
    for(int i=0;i<n;i++){
        // printf("%d ",arr[i]);
    }

    double t1 = omp_get_wtime(); //gets the time
    mergeSort(arr,0,n-1);
    double t2 = omp_get_wtime(); //gets the time after func call.

    printf("\nThe time taken is: %f",t2-t1);

    // printf("\nThe sorted array is:\n");
    for(int i=0;i<n;i++){
        // printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;

}