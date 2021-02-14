#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>
int num_points;
int dataPoints[100][2];
int cluster_points[4][2] = {{25,25},{25,75},{75,25},{75,75}};
int clusterCounts[4];

void populate_points(){
    int i = 0;
    #pragma omp parallel for private(i)
    for(i=0;i<num_points;i++){
        dataPoints[i][0] = rand()%100;
        dataPoints[i][1] = rand()%100;
    }
    for(int i=0;i<4;i++){
        clusterCounts[i] = 0;
    }
}

double getDistance(int x1,int y1,int x2, int y2){
    double ans = sqrt(((x2-x1)*(x2-x1)) + ((y2-y1)*(y2-y1)));
    return ans;
}

void classifyPoints(){
    omp_set_num_threads(4);
    int i,j;
    double min_dist = 99999;
    double curr_dist = 0;
    int index = 0;
    #pragma omp parallel for private(i,j,curr_dist,min_dist,index)
    for(i=0;i<num_points;i++){
        printf("%d hi ",omp_get_thread_num());
        curr_dist = 0;
        min_dist = 99999;
        index = -1;
        for(j=0;j<4;j++){

            curr_dist= getDistance(dataPoints[i][0],dataPoints[i][1],cluster_points[j][0],cluster_points[j][1]);
            if(curr_dist < min_dist){
                min_dist = curr_dist;
                index = j;
            }
        }

        // printf("\nData point (%d,%d) is assigned to cluster %d",dataPoints[i][0],dataPoints[i][1],index);
        clusterCounts[index]++;
    }
}

void main(){
    printf("\n Enter the number of points to be populated:\t");
    scanf("%d",&num_points);
    printf("h %d",num_points);
    // Populate all the points 
    populate_points();
    printf("\n The points are:\t");
    // for(int i=0;i<num_points;i++){
    //     printf("\n%d %d", dataPoints[i][0], dataPoints[i][1]);
    // }
    printf("\n");
    // // Classifiy ponts
    classifyPoints();
    printf("\n");
    // for(int i=0;i<4;i++){
    //     printf("\nCluster %d has %d points",i,clusterCounts[i]);
    // }
}