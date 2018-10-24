#ifndef HOMEWORK_H1
#define HOMEWORK_H1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <math.h>

#define MAXVAL 255
#define BLACK 0

typedef unsigned char pixel; // pixel from image

typedef struct {
    int width, height, max_value, type;
    pixel** matrix;
} image;

void initialize(image *im);
void render(image *im);
void writeData(const char * fileName, image *img);
int calculateDistance (int x, int y);

#endif /* HOMEWORK_H1 */