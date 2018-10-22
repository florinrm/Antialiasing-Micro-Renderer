#include "homework.h"

int num_threads;
int resize_factor;

u_int gaussianMatrix[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}}, gaussianMean = 16;

pthread_t threads[8];
int threads_id[8];

pthread_barrier_t barrier;
pthread_mutex_t mutex;

imageConverter conv;


void readInput(const char * fileName, image *img) {
    
    FILE *input = fopen(fileName, "rb");
    if (input == NULL)
        return;

    image *buff;

    buff = (image*) malloc (sizeof(image));
    char buffRead[2];
    fscanf(input, "%c %c", &buffRead[0], &buffRead[1]);
    buff->type = buffRead[1] - '0';
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


void *threadFunction(void *var) {
    imageConverter *convert = (imageConverter *)var;
    image *in = convert->in;
    image *out = convert->out; /*
    if (in == NULL)
        return; */
    image *buff = (image *) malloc (sizeof(image));
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

    for (int i = 0; i < buff->height; ++i) {
        for (int j = 0; j < buff->width; ++j) {
            //pthread_barrier_wait(&barrier);
            if (resize_factor % 2 == 0) {

                int top_left_i = resize_factor * i;
                int top_left_j = resize_factor * j;
                int bottom_right_i = resize_factor * (i + 1);
                int bottom_right_j = resize_factor * (j + 1);

                unsigned int counter = 0;
                if (in->type == COLOR) {

                    unsigned int sumRed = 0, sumGreen = 0, sumBlue = 0;
                    for (int x = top_left_i; x < bottom_right_i; ++x) {
                        for (int y = top_left_j; y < bottom_right_j; ++y) {
                            sumRed += (u_int) in->color_image[x][y].red;
                            sumGreen += (u_int) in->color_image[x][y].green;
                            sumBlue += (u_int) in->color_image[x][y].blue;
                            ++counter;
                        }
                    }

                    buff->color_image[i][j].red = (unsigned char) (sumRed / counter);
                    buff->color_image[i][j].green = (unsigned char) (sumGreen / counter);
                    buff->color_image[i][j].blue = (unsigned char) (sumBlue / counter);

                } else if (in->type == GRAYSCALE) {

                    unsigned int totalSum = 0;
                    for (int x = top_left_i; x < bottom_right_i; ++x) {
                        for (int y = top_left_j; y < bottom_right_j; ++y) {
                            totalSum += in->gray_image[x][y].gray;
                            ++counter;
                        }
                    }

                    buff->gray_image[i][j].gray = (unsigned char) (totalSum / counter);
                }


            } else if (resize_factor % 3 == 0) {
                if (in->type == COLOR) {

                    unsigned int sumRed = 0, sumGreen = 0, sumBlue = 0;
                    for (int x = 0; x < 3; ++x) {
                        for (int y = 0; y < 3; ++y) {
                            sumRed += in->color_image[x + 3 * i][y + 3 * j].red * gaussianMatrix[x][y];
                            sumGreen += in->color_image[x + 3 * i][y + 3 * j].green * gaussianMatrix[x][y];
                            sumBlue += in->color_image[x + 3 * i][y + 3 * j].blue * gaussianMatrix[x][y];
                        }
                    }
                    buff->color_image[i][j].red = (unsigned char) (sumRed / gaussianMean);
                    buff->color_image[i][j].green = (unsigned char) (sumGreen / gaussianMean);
                    buff->color_image[i][j].blue = (unsigned char) (sumBlue / gaussianMean);

                } else if (in->type == GRAYSCALE) {

                    unsigned int totalSum = 0;
                    for (int x = 0; x < 3; ++x) {
                        for (int y = 0; y < 3; ++y) {
                            totalSum += in->gray_image[x + 3 * i][y + 3 * j].gray * gaussianMatrix[x][y];
                        }
                    }
                    buff->gray_image[i][j].gray = (unsigned char) (totalSum / gaussianMean);
                }
            }
        }
    }
    *out = *buff;
    free(buff);
}

void resize(image *in, image * out) {
    imageConverter img;
    img.in = in;
    img.out = out;
    pthread_barrier_init(&barrier, NULL, num_threads);

    for (int i = 0; i < num_threads; ++i) {
        threads_id[i] = i;
    }
    for (int i = 0; i < num_threads; ++i) {
        pthread_create(&(threads[i]), NULL, threadFunction, (void *)&img);
    }
    for (int i = 0; i < num_threads; ++i)
        pthread_join(threads[i], NULL);
    pthread_barrier_destroy(&barrier);

}