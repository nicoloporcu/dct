#include <stdlib.h>
#include <stdio.h>
#include "dct.h"
#define input_file  "input.raw"
#define output_file "output.raw"

#define h  800 
#define w  800

int main(int argc, char** argv){
    unsigned char *a = (unsigned char*) malloc (sizeof(unsigned char)*h*w);
    double * y = (double*) malloc (sizeof(double)*h*w);
    
    DCT dct_solver; 


    FILE *fp;
    if (!(fp=fopen(input_file, "rb"))) {
		printf("can not opern file\n");
		return 1;
	}
	fread(a, sizeof(unsigned char), w*h, fp);
	fclose(fp);
    
    dct_solver.block_dct(a, y, w, h, 8);
    printf("%f", y[400*800 +400]);

    free(a);
    free(y);

    return 0;
}