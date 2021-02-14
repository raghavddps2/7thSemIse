#include<stdio.h>
#include<omp.h>
#include<gd.h>

void main(){
    char *input_file = "/home/learner/Desktop/a1.png";
    char *output_file = "/home/learner/Desktop/a4.png";

    FILE *fp;
    fp = fopen(input_file,"r");

    if(fp == NULL){
        printf("\n Error Opening file.");
        exit(0);
    }

    gdImagePtr image = gdImageCreateFromPng(fp); //create gdImagePtr object
    int color,red,green,blue;
    int i,j;
    int width = gdImageSX(image); //get width
    int height = gdImageSY(image); //get height
    int combined;

    #pragma omp parallel for private(j,color,red,blue,green,combined)
    for(i=0;i<width;i++){

        #pragma omp critical
        {
            for(j=0;j<height;j++){
                color = gdImageGetPixel(image,i,j); //get pixel
                red = gdImageRed(image,color);
                green = gdImageGreen(image,color);
                blue = gdImageBlue(image,color);

                combined = 0.33*red + 0.33*green + 0.34*blue;
                color = gdImageColorAllocate(image,combined,combined,combined); //allocate color
                gdImageSetPixel(image,i,j,color); //set pixel
            }
        }
    }

    fp = fopen(output_file,"w");
    if(fp == NULL){
        printf("Error writing to file");
        exit(0);
    }

    gdImagePng(image,fp); //write to png file
    gdImageDestroy(image);
    fclose(fp);
    printf("File size: %d x %d", width, height);
}