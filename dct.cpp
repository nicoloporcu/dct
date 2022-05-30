#include <math.h> 
//#include <stdlib.h>
//#include <stdio.h>
#include "dct.h"

#define PI 3.14159265

#define input_file  "input.raw"
#define output_file "output.raw"


#define h  800 
#define w  800

using namespace std;

 void DCT::horizontal_fct_help(double ** x, double ** temp, int size){
    int block_size = size;
    for(int row = 0; row < size ; ++row){
        while(block_size> 1){
            block_size = block_size/2;

            for(int start = 0; start < size; start += 2*block_size ){
                for(int i =0; i < block_size;++i){
                    double a = x[row][start + i];
                    double b = x[row][start + 2*block_size - 1 -i];
                    temp[row][start + i] = a+b;
                    temp[row][start + i +block_size] = (a-b)/(2*cos((i+0.5)*PI/(2*block_size)));
                }
            }

            double * buff = x[row];
            x[row] = temp[row];
            temp[row] = buff;
        }

        block_size = 1;

        while(block_size< size){
            for(int start = 0; start < size ; start += 2*block_size ){
                for(int i =0; i < block_size-1;++i){
                    temp[row][start + i * 2 ] = x[row][start +i];
                    temp[row][start + i*2 +1] = x[row][start + i + block_size] + x[row][start +i + block_size + 1];
                }
                temp[row][start + 2*block_size - 2] = x[row][start + block_size - 1];
                temp[row][start+ 2*block_size - 1] = x[row][start + 2*block_size - 1];
            }

            block_size *= 2;
            double * buff = x[row];
            x[row] = temp[row];
            temp[row] = buff;
        }
    }
}


void DCT::vertical_fct_help(double ** x, double ** temp, int size){
    int block_size = size;
    for(int col = 0; col < size ; ++col){
        while(block_size> 1){
            block_size = block_size/2;

            for(int start = 0; start < size; start += 2*block_size ){
                for(int i =0; i < block_size;++i){
                    double a = x[start + i][col];
                    double b = x[start + 2*block_size - 1 -i][col];
                    temp[start + i][col] = a+b;
                    temp[start + i +block_size][col] = (a-b)/(2*cos((i+0.5)*PI/(2*block_size)));
                }
            }

            for(int i = 0; i < size; ++i){
                x[i][col] = temp[i][col];
            }
        }

        block_size = 1;

        while(block_size< size){
            for(int start = 0; start < size; start += 2*block_size ){
                for(int i =0; i < block_size-1;++i){
                    temp[start + i * 2 ][col] = x[start +i][col];
                    temp[start + i*2 +1][col] = x[start + i + block_size][col] + x[start +i + block_size + 1][col];
                }
                temp[start + 2*block_size - 2][col] = x[start + block_size - 1][col];
                temp[start+ 2*block_size - 1][col] = x[start + 2*block_size - 1][col];
            }

            block_size *= 2;
            for(int i = 0; i < size; ++i){
                x[i][col] = temp[i][col];
            }
        }
    }
}




double * DCT::TWOdim_naive_DCT(unsigned char * x, double * y, int size){
    for(int row =0; row < size; ++row){
        for( int col = 0; col < size; ++col ){
            y[row*size + col] = 0;
            for(int n = 0; n < size; ++n){
                y[row*size + col] += x[row*size + n] * cos( (PI/size) *(n+0.5)* col);
            }
        }
        for( int k = 0; k < size; ++k ){
            x[row*size+ k] = y[row*size + k];
        }
    }
    
    
    for(int col =0; col < size; ++col){
        for( int row = 0; row < size; ++row ){
            y[row * size +col] = 0;
            for(int n = 0; n < size; ++n){
                y[row*size+ col] += x[n*size +col] * cos( (PI/size) *(n+0.5)* row);
            }
        }
    }

    return y;
}


void DCT::section_fct(unsigned char *x , double * y, int & width, int & height, int  & blocksize, int & block_x, int & block_y){
    double ** segment_in = new double*[blocksize];
    double ** temp = new double * [blocksize];

    int start_row = block_x *  blocksize;
    int start_col = block_y * blocksize;
    
    for(int row = 0; row < blocksize; row++){
        segment_in[row] = new double[blocksize];
        temp[row] = new double[blocksize];
        for(int col = 0; col < blocksize; col++){
            segment_in[row][col] = x[(row +start_row)* width + start_col + col ];
        }
    }

    DCT::horizontal_fct_help(segment_in, temp, blocksize);
    DCT::vertical_fct_help(segment_in, temp, blocksize);

    for(int row = 0; row < blocksize; row++){

        for(int col = 0; col < blocksize; col++){
            y[(row +start_row)* width + start_col + col ] = segment_in[row][col];
        }

        delete [] segment_in[row];
        delete [] temp[row];
    }
    delete [] segment_in;
    delete [] temp;
}


void DCT::block_dct(unsigned char * x, double * y, int width, int height, int blocksize){

    //cout << width <<" " << height << endl;
    if (width % blocksize != 0 || height% blocksize != 0 ){
        //printf("DCT Error: Image not evenly divisible into blocks of size %d", size);
    }
    int num_blocks_w = width / blocksize;
    int num_blocks_h = height / blocksize;
    for( int block_x = 0; block_x < num_blocks_h; block_x ++){
        for( int block_y = 0; block_y < num_blocks_w; block_y ++){


            section_fct(x, y, width, height, blocksize, block_x, block_y);

        }
    }

}
