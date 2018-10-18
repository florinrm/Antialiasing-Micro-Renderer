#include "homework1.h"

int num_threads;
int resolution;

int max = 100;

void initialize(image *im) {
    im = (image *) malloc (sizeof(image));
    im->width = resolution;
    im->height = resolution;
    im->max_value = MAXVAL;
    im->type = 5;
    im->matrix = (pixel **) malloc (resolution * sizeof(pixel *));

    for (int i = 0; i < resolution; ++i) {
        im->matrix[i] = (pixel *) malloc (resolution * sizeof(pixel));
    }
    for (int i = 0; i < resolution; ++i) {
        for (int j = 0; j < resolution; ++j)
            im->matrix[i][j] = MAXVAL;
    }

}

void render(image *im) {
    int resolution_scale = resolution / max;
    for (int i = 0; i < max; ++i) {
        for (int j = 0; j < max; ++j) {
            double distance = abs((-1) * i + 2 * j) / sqrt(1 + 4); // (-1) ^ 2 + 2 ^ 2
            if (distance < 3) {
                for (int x = 0; x < resolution_scale; ++x) {
                    for (int y = 0; y < resolution_scale; ++y) {
                        im->matrix[x + resolution_scale * i][y + resolution_scale * j] = MAXVAL;
                    }
                }
            }
        }
    }
}

void writeData(const char * fileName, image *img) {
    FILE *output = fopen(fileName, "wb");
    fprintf(output, "P%d\n%d %d\n%d\n", img->type, img->width, img->height, img->max_value);

    for (int i = 0; i < img->height; ++i)
        fwrite(img->matrix[i], sizeof(pixel), img->width, output);

    for (int i = 0; i < img->height; ++i) {
        free(img->matrix[i]);
    }
    free(img->matrix);
    free(img);
    
    fclose(output);
}

