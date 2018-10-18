#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR 5
#define GRAYSCALE 6

typedef struct {
    unsigned char red, green, blue;
} rgb;

typedef struct {
    unsigned char gray;
} gray;

typedef struct {
    int width, height, max_size;
    int type;
    rgb **color_image; // 5 type
    gray **gray_image; // 6 type
} image;

typedef struct {
    image *in, *out;
} imageConverter;

void readInput(const char * fileName, image *img);

void writeData(const char * fileName, image *img);

void resize(image *in, image * out);

#endif /* HOMEWORK_H */