#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <complex.h>
#include <string.h>
#include <pthread.h>
#define REAL_DIM 104
#define IMAGINARY_DIM 104
#define MAX_IT 80
#define THREADS 4
pthread_t tid[THREADS*2];
char stri[20000] = "";

struct parameters{
         int x;
         int y;
         double h;
         double w;
};

    void mandelbrot(void *received_struct) {
    struct parameters *info = (struct parameters*) received_struct;
    double realDim = info->x;
    double imaginaryDim = info->y;
    double width = info->w;
    double height = info->h;
    width = realDim + width;
    height = imaginaryDim + height;
    double realStart = -2.0f;
    double realEnd = 1.0f;
    double imaginaryStart = -1.0f;
    double imaginaryEnd = 1.0f;
         for (int i = realDim; i < width; i++) {
                 for (int j = imaginaryDim; j < height; j++) {
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
    }

    int main() {
        struct parameters info;
                info.x = 0;
                info.y = 0;
                info.w = REAL_DIM/2;
                info.h = IMAGINARY_DIM/2;
        pthread_create(&tid[0], NULL, mandelbrot,  &info);
                info.x = REAL_DIM/2;
                info.y = 0;
                info.w = REAL_DIM/2;
                info.h = IMAGINARY_DIM/2;
        pthread_create(&tid[1], NULL, mandelbrot,  &info);

                info.x = 0;
                info.y = IMAGINARY_DIM/2;
                info.w = REAL_DIM/2;
                info.h = IMAGINARY_DIM/2;
        pthread_create(&tid[2], NULL, mandelbrot,  &info);

                info.x = REAL_DIM/2;
                info.y = IMAGINARY_DIM/2;
                info.w = REAL_DIM/2;
                info.h = IMAGINARY_DIM/2;
        pthread_create(&tid[3], NULL, mandelbrot,  &info);



                info.x = 0;
                info.y = IMAGINARY_DIM/2;
                info.w = REAL_DIM/4;
                info.h = IMAGINARY_DIM/2;
        pthread_create(&tid[4], NULL, mandelbrot,  &info);
                info.x = REAL_DIM/4;
                info.y = IMAGINARY_DIM/2;
                info.w = REAL_DIM/4;
                info.h = IMAGINARY_DIM/2;
        pthread_create(&tid[5], NULL, mandelbrot,  &info);

                info.x = REAL_DIM/4 + REAL_DIM/4;
                info.y = IMAGINARY_DIM/2;
                info.w = REAL_DIM/4;
                info.h = IMAGINARY_DIM/2;
        pthread_create(&tid[6], NULL, mandelbrot,  &info);

                info.x = REAL_DIM/4 + REAL_DIM/4 + REAL_DIM/4;
                info.y = IMAGINARY_DIM/2;
                info.w = REAL_DIM/4;
                info.h = IMAGINARY_DIM/2;
        pthread_create(&tid[7], NULL, mandelbrot,  &info);


        

        for(int k = 0; k<4; k++) {
            pthread_join(tid[k], NULL);
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

