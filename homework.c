#include "homework.h"

#define min(x, y) (((x) < (y)) ? (x) : (y))

int num_threads;
int resize_factor;

u_int gaussianMatrix[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}}, gaussianMean = 16;

pthread_t threads[8];
int threads_id[8];

imageConverter conv;


void readInput(const char * fileName, image *img) {
    
    FILE *input = fopen(fileName, "rb");
    if (input == NULL)
        return;

    image *buff; // reference used for creating the original image

    buff = (image*) malloc (sizeof(image));
    char buffRead[2];
    fscanf(input, "%c %c", &buffRead[0], &buffRead[1]);
    buff->type = buffRead[1] - '0'; // from char to int
    fscanf(input, "%d %d\n%d\n", &buff->width, &buff->height, &buff->max_size);

    if (buff->type == COLOR) {
        
        buff->color_image = (rgb**) malloc (buff->height * sizeof(rgb*));

        for (int i = 0; i < buff->height; ++i)
            buff->color_image[i] = (rgb *) malloc (buff->width * sizeof(rgb));

        for (int i = 0; i < buff->height; ++i)
            fread(buff->color_image[i], sizeof(rgb), buff->width, input);

    } else if (buff->type == GRAYSCALE) {

        buff->gray_image = (gray**) malloc (buff->height * sizeof(gray*));
        
        for (int i = 0; i < buff->height; ++i)
            buff->gray_image[i] = (gray *) malloc (buff->width * sizeof(gray));

        for (int i = 0; i < buff->height; ++i)
            fread(buff->gray_image[i], sizeof(gray), buff->width, input);
    }

    *img = *buff;
    free(buff);

    fclose(input);
}

void writeData(const char * fileName, image *img) {

    FILE *output = fopen(fileName, "wb");
    if (output == NULL)
        return;
    fprintf(output, "P%d\n%d %d\n%d\n", img->type, img->width, img->height, img->max_size);
    if (img->type == COLOR) {
        for (int i = 0; i < img->height; ++i) { 
            
            for (int j = 0; j < img->width; ++j) {
                fwrite(&img->color_image[i][j].red, sizeof(unsigned char), 1, output);
                fwrite(&img->color_image[i][j].green, sizeof(unsigned char), 1, output);
                fwrite(&img->color_image[i][j].blue, sizeof(unsigned char), 1, output);
            }
        }
    } else if (img->type == GRAYSCALE) {
        for (int i = 0; i < img->height; ++i)
            for (int j = 0; j < img->width; ++j)
                fwrite(&img->gray_image[i][j], sizeof(unsigned char), 1, output);
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
}

image *buff; // used for image resize in thread function

void* threadFunction(void *var) {
    int tid = *(int *) var;
    
    // chunk for every thread
    int start = tid * ceil ((double) buff->width / (double) num_threads);
    int end = min(buff->width, (tid + 1) * ceil((double) buff->width / (double) num_threads));

    for (int i = 0; i < buff->height; ++i) {
        for (int j = start; j < end; ++j) {
            if (resize_factor % 2 == 0) {

                int top_left_i = resize_factor * i;
                int top_left_j = resize_factor * j;
                int bottom_right_i = resize_factor * (i + 1);
                int bottom_right_j = resize_factor * (j + 1);

                unsigned int counter = 0;
                if (conv.in->type == COLOR) {

                    unsigned int sumRed = 0, sumGreen = 0, sumBlue = 0;
                    for (int x = top_left_i; x < bottom_right_i; ++x) {
                        for (int y = top_left_j; y < bottom_right_j; ++y) {
                            sumRed += (u_int) conv.in->color_image[x][y].red;
                            sumGreen += (u_int) conv.in->color_image[x][y].green;
                            sumBlue += (u_int) conv.in->color_image[x][y].blue;
                            ++counter;
                        }
                    }

                    buff->color_image[i][j].red = (u_char) (sumRed / counter);
                    buff->color_image[i][j].green = (u_char) (sumGreen / counter);
                    buff->color_image[i][j].blue = (u_char) (sumBlue / counter);

                } else if (conv.in->type == GRAYSCALE) {

                    unsigned int totalSum = 0;
                    for (int x = top_left_i; x < bottom_right_i; ++x) {
                        for (int y = top_left_j; y < bottom_right_j; ++y) {
                            totalSum += conv.in->gray_image[x][y].gray;
                            ++counter;
                        }
                    }

                    buff->gray_image[i][j].gray = (unsigned char) (totalSum / counter);
                }


            } else if (resize_factor % 3 == 0) {
                if (conv.in->type == COLOR) {

                    unsigned int sumRed = 0, sumGreen = 0, sumBlue = 0;
                    for (int x = 0; x < 3; ++x) {
                        for (int y = 0; y < 3; ++y) {
                            sumRed += conv.in->color_image[x + 3 * i][y + 3 * j].red * gaussianMatrix[x][y];
                            sumGreen += conv.in->color_image[x + 3 * i][y + 3 * j].green * gaussianMatrix[x][y];
                            sumBlue += conv.in->color_image[x + 3 * i][y + 3 * j].blue * gaussianMatrix[x][y];
                        }
                    }
                    buff->color_image[i][j].red = (u_char) (sumRed / gaussianMean);
                    buff->color_image[i][j].green = (u_char) (sumGreen / gaussianMean);
                    buff->color_image[i][j].blue = (u_char) (sumBlue / gaussianMean);

                } else if (conv.in->type == GRAYSCALE) {

                    unsigned int totalSum = 0;
                    for (int x = 0; x < 3; ++x) {
                        for (int y = 0; y < 3; ++y) {
                            totalSum += conv.in->gray_image[x + 3 * i][y + 3 * j].gray * gaussianMatrix[x][y];
                        }
                    }
                    buff->gray_image[i][j].gray = (unsigned char) (totalSum / gaussianMean);
                }
            }
        }
    }
    *conv.out = *buff;
}

void resize(image *in, image * out) {
    buff = (image *) malloc (sizeof(image));
    buff->type = in->type;
    buff->height = in->height / resize_factor;
    buff->width = in->width / resize_factor;
    buff->max_size = in->max_size;
    if (buff->type == COLOR) {
        buff->color_image = (rgb **) malloc (buff->height * sizeof(rgb *));
        for (int i = 0; i < buff->height; ++i)
            buff->color_image[i] = (rgb *) malloc (buff->width * sizeof(rgb));
    } else if (buff->type == GRAYSCALE) {
        buff->gray_image = (gray **) malloc (buff->height * sizeof(gray *));
        for (int i = 0; i < buff->height; ++i)
            buff->gray_image[i] = (gray *) malloc (buff->width * sizeof(gray));
    }
    conv.in = in;
    conv.out = out;
    for (int i = 0; i < num_threads; ++i) {
        threads_id[i] = i;
    }
    for (int i = 0; i < num_threads; ++i) {
        pthread_create(&(threads[i]), NULL, threadFunction, &threads_id[i]);
    }
    for (int i = 0; i < num_threads; ++i)
        pthread_join(threads[i], NULL);
    *out = *conv.out;
    free(buff);
    if (in->type == COLOR) {
        for (int i = 0; i < in->height; ++i)
            free(in->color_image[i]);
        free(in->color_image);
    } else if (in->type == GRAYSCALE) {
        for (int i = 0; i < in->height; ++i)
            free(in->gray_image[i]);
        free(in->gray_image);
    }
}