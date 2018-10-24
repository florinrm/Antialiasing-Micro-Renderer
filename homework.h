#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define COLOR 6
#define GRAYSCALE 5

typedef struct {
    unsigned char red, green, blue;
} rgb; 

typedef struct {
    unsigned char gray;
} gray; // grayscale image

typedef struct {
    int width, height, max_size;
    int type; // image type
    rgb **color_image; // 5 type
    gray **gray_image; // 6 type
} image;

typedef struct {
    image *in, *out;
} imageConverter; // structure used for image resize

void readInput(const char * fileName, image *img);

void writeData(const char * fileName, image *img);

void resize(image *in, image * out);

void *threadFunction (void *var);


#endif /* HOMEWORK_H */