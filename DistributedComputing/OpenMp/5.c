/*
    Write an OpenMP parallel program for Points Classification.
    Prove the correctness of Sequential program with that if parallel.

*/
#include<stdio.h>
#include<omp.h>
#include<math.h>
#include<stdlib.h>
#define K 4

int num_threads;
int num_points, cluster_count[K];
int datapoints[100][2];
int cluster[K][2] = {{75,25},{25,25},{25,75},{75,75}};

double get_distance(int x1,int y1,int x2,int y2){
    return (double)(sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
}

void populate_points1(){
    int i;
    // #pragma omp parallel
    for(i=0;i<num_points;i++){
        datapoints[i][0] = rand()%100;
        datapoints[i][1] = rand()%100;
        printf("\nData Point %d: %d,%d",i,datapoints[i][0],datapoints[i][1]);
    }

    for(i=0;i<K;i++){
        cluster_count[i] = 0;
    }
}

void populate_points(){
    int i;
    // #pragma omp parallel
    for(i=0;i<num_points;i++){
        datapoints[i][0]=rand()%100;
        datapoints[i][1]=rand()%100;
        printf("\nData Point %d: %d,%d",i,datapoints[i][0],datapoints[i][1]);
    }
    for(i=0;i<4;i++)
        cluster_count[i]=0;
}

void classify_points(){
    int cluster_no;
    double min_distance = 999;
    double dis = 0;
    int i,j;
    #pragma omp parallel for private(cluster_no,min_distance,dis,j,i)
    for(i=0;i<num_points;i++){

        cluster_no = -1;
        dis = 0;
        min_distance = 999;
        for(j=0;j<K;j++){
            dis = get_distance(datapoints[i][0],datapoints[i][1],cluster[j][0],cluster[j][1]);
            if(dis < min_distance){
                min_distance = dis;
                cluster_no = j;
            }
        }

        printf("\n%d,%d belongs to cluster %d,%d with cluster no %d",datapoints[i][0],datapoints[i][1],
        cluster[cluster_no][0],cluster[cluster_no][1],cluster_no);
        cluster_count[cluster_no]++;
    }
}



void main(){
    printf("Max Threads:%d\n",omp_get_max_threads());
    printf("Max Threads:%d\n",omp_get_num_threads());
    printf("Enter the number of points:\t");
    scanf("%d",&num_points);

    //Once we took points as the input, our next step is to populate the point.
    populate_points();


    double t1 = omp_get_wtime();
    classify_points();
    double t2 = omp_get_wtime();
    printf("\nTime taken is: %lf\n",t2-t1);
    printf("\nCounts in clusters:\n");
    for(int i=0;i<K;i++){
        printf("%d--->%d\n",i,cluster_count[i]);
    }
}