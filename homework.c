#include "homework.h"

int num_threads;
int resize_factor;

int gaussianMatrix[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};

pthread_t threads[8];
int threads_id[8];

void readInput(const char * fileName, image *img) {
    
    FILE *input = fopen(fileName, "rb");
    if (input == NULL)
        return;

    img = (image*) malloc (sizeof(image));
    char buffRead[2];
    fscanf(input, "%c %c", &buffRead[0], &buffRead[1]);
    img->type = buffRead[1] = '0';
    fscanf(input, "%d %d", &img->width, &img->height);
    fscanf(input, "%d", &img->max_size);

    if (img->type == COLOR) {
        img->color_image = (rgb**) malloc (img->height * sizeof(rgb*));
        for (int i = 0; i < img->height; ++i)
            img->color_image[i] = (rgb *) malloc (img->width * sizeof(rgb));
        for (int i = 0; i < img->height; ++i)
            fread(img->color_image[i], sizeof(rgb), img->width, input);
    } else if (img->type == GRAYSCALE) {
        img->gray_image = (gray**) malloc (img->height * sizeof(gray*));
        for (int i = 0; i < img->height; ++i)
            img->gray_image[i] = (gray *) malloc (img->width * sizeof(gray));
        for (int i = 0; i < img->height; ++i)
            fread(img->gray_image[i], sizeof(gray), img->width, input);
    }

    fclose(input);
}

void writeData(const char * fileName, image *img) {

    FILE *output = fopen(fileName, "wb");
    if (output == NULL)
        return;
    fprintf(output, "P%d\n%d %d\n%d\n", img->type, img->width, img->height, img->max_size);
    if (img->type == COLOR) {
        for (int i = 0; i < img->height; ++i)
            fwrite(img->color_image[i], sizeof(rgb), img->width, output);
    } else if (img->type == GRAYSCALE) {
        for (int i = 0; i < img->height; ++i)
            fwrite(img->gray_image[i], sizeof(gray), img->width, output);
    }

    fclose(output);

    if (img->type == COLOR) {
        for (int i = 0; i < img->height; ++i)
            free(img->color_image[i]);
        free(img->color_image);
    } else if (img->type == GRAYSCALE) {
        for (int i = 0; i < img->height; ++i)
            free(img->gray_image[i]);
        free(img->gray_image);
    }
    free(img);
}

void *threadFunction(void *var) {

}

void resize(image *in, image * out) { 
    if (in == NULL)
        return;
    out = (image *) malloc (sizeof(image));
    out->type = in->type;
    out->height = in->height / resize_factor;
    out->width = in->width / resize_factor;

    if (resize_factor % 2 == 0) {
        
    } else if (resize_factor % 3 == 0) {

    }
}