#include "homework1.h"

int num_threads;
int resolution;

int max = 100;

void initialize(image *im) {
    image *buff;
    buff = (image *) malloc (sizeof(image));
    buff->width = resolution;
    buff->height = resolution;
    buff->max_value = MAXVAL;
    buff->type = 5;
    buff->matrix = (pixel **) malloc (resolution * sizeof(pixel *));

    for (int i = 0; i < resolution; ++i) {
        buff->matrix[i] = (pixel *) malloc (resolution * sizeof(pixel));
    }
    for (int i = 0; i < resolution; ++i) {
        for (int j = 0; j < resolution; ++j)
            buff->matrix[i][j] = MAXVAL;
    }
    *im = *buff;
    free(buff);

}

void *threadFunction (void *var) {
    
}

void render(image *im) {
    int resolution_scale = resolution / max;
    for (int i = 0; i < max; ++i) {
        for (int j = 0; j < max; ++j) {
            double distance = abs((-1) * i + 2 * j) / sqrt(1 + 4); // (-1) ^ 2 + 2 ^ 2
            if (distance < 3) {
                for (int x = 0; x < resolution_scale; ++x) {
                    for (int y = 0; y < resolution_scale; ++y) {
                        im->matrix[x + resolution_scale * i][y + resolution_scale * j] = BLACK;
                    }
                }
            }
        }
    }
}

void writeData(const char * fileName, image *img) {
    FILE *output = fopen(fileName, "wb");
    fprintf(output, "P%d\n%d %d\n%d\n", img->type, img->width, img->height, img->max_value);

    for (int i = img->width - 1; i >= 0; --i) {
        for (int j = 0; j < img->height; ++j) {
            fwrite(&img->matrix[j][i], sizeof(pixel), 1, output);
        }
    }
    for (int i = 0; i < img->height; ++i) {
        free(img->matrix[i]);
    }
    free(img->matrix);
    
    fclose(output);
}

