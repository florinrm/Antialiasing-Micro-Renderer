#ifndef HOMEWORK_H1
#define HOMEWORK_H1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define MAXVAL 255
#define BLACK 0

typedef unsigned char pixel;

typedef struct {
    int width, height, max_value, type;
    pixel** matrix;
} image;

void initialize(image *im);
void render(image *im);
void writeData(const char * fileName, image *img);

#endif /* HOMEWORK_H1 */