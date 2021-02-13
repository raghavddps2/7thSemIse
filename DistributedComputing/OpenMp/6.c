#include<stdio.h>
#include<gd.h> //This is the graphics-draw header file. -lgd used for compilation
#include<string.h>
#include<omp.h>

int main(){
    //Defines the name of the input and the output image.
    char *input_file = "/home/learner/Desktop/a1.png";
    char *output_file = "/home/learner/Desktop/a2.png";

    //Determines the number of threads.
    int num_threads = 2;
    int color, x, y,i;
    int red, green, blue;

    FILE *fp;

    //Check if the file is not proper.
    if((fp = fopen(input_file,"r")) == NULL){
        printf("\nError opening input file %s\n", input_file);
        return 1;
    }

    //we get the graphics-draw image ptr 
    gdImagePtr img = gdImageCreateFromPng(fp);
    int width = gdImageSX(img);
    int height = gdImageSY(img);
    int combined;

    double t1 = omp_get_wtime();

    //each of the variable will be priavte,
    #pragma omp parallel for private(y,color,red,green,blue,combined)
    for(x=0;x<width;x++){
        //we have a critical section now
        #pragma omp critical
        {
            for(y=0;y<height;y++){
                color = gdImageGetPixel(img,x,y); //get the pixel
                //get red, blue and green components
                red = gdImageRed(img,color);
                green = gdImageGreen(img,color);
                blue = gdImageBlue(img,color);
                
                //TODO - How the formula came.
                combined = 0.3*red + 0.59*green + 0.11*blue;
                color = gdImageColorAllocate(img,combined,combined,combined); 
                gdImageSetPixel(img,x,y,color); //set the particular pixel.
            }
        }
    }

    double t2 = omp_get_wtime();
    
    fp = fopen(output_file,"w");
    if(fp == NULL){
        printf("\nError opening output file %s", output_file);
        return 1;
    }

    gdImagePng(img,fp); //put image in fp
    gdImageDestroy(img); //destriy gd ref.
    fclose(fp);
    printf("\nFile Size: %d x %d",width,height);
    printf("\nTime Taken: %.31fms\n",(t2-t1)*1000);
    return 0;


}