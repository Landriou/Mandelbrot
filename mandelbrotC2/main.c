#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <complex.h>
#include <string.h>
#define REAL_DIM 101
#define IMAGINARY_DIM 101
#define MAX_IT 80
char stri[20000] = "";
    void mandelbrot() {
      double realStart = -2.0f;
      double realEnd = 1.0f;
      double imaginaryStart = -1.0f;
      double imaginaryEnd = 1.0f;
         for (int i = 0; i < REAL_DIM; i++) {
                 for (int j = 0; j < IMAGINARY_DIM; j++) {
                    double complex c = (realStart + ((double) i / (double) REAL_DIM) * (realEnd - realStart)) + I*(imaginaryStart + ((double) j/ (double) IMAGINARY_DIM) * (imaginaryEnd - imaginaryStart));
                    double complex z = 0;

                     
                    int iterations = 0;
                    while (cabs(z) <= 2 && iterations < MAX_IT) {
                        z = z*z + c;
                        iterations++;
                    }
                    if (iterations == MAX_IT) { 
                        strcat(stri, "0");
                    }
                    else {
                        strcat(stri, ".");
                    }
                 } 
             }
    
    FILE *f = fopen("out.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "%s", stri);

    fclose(f);
     }

    int main() {
       
        mandelbrot();
        
    }



