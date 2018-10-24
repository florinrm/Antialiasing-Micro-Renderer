#include "homework1.h"

#define min(x, y) (((x) < (y)) ? (x) : (y))

int num_threads;
int resolution;

int max = 100;

pthread_t threads[8];
int threads_id[8];

void initialize(image *im) {
    image *buff; // reference used in image initializing
    buff = (image *) malloc (sizeof(image));
    buff->width = resolution;
    buff->height = resolution;
    buff->max_value = MAXVAL;
    buff->type = 5; // B&W image
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

image *feck; // global variable used for threading function in order

int calculateDistance(int i, int j) {
    return abs((-1) * i + 2 * j) / sqrt(1 + 4);
}

void *threadFunction (void *var) {
    int tid = *(int *) var;

    int start = tid * ceil((double) resolution / (double) num_threads);
    int end = min(resolution, (tid + 1) * ceil((double) resolution / (double) num_threads));

    for (int i = 0; i < resolution; i++) {
		for (int j = start; j < end; j++) {
            // calculating the distance between 2 coordonates
			if (abs((-1 * ((j + 0.5f) * 100.0f / (float)resolution)) 
                + (2 * (((float)resolution - 1 - (i - 0.5f)) * 100.0F / resolution))) / sqrt(5) <= 3.0f) {
				feck->matrix[i][j] = 0;
			}
		}
	}
}

void render(image *im) {
    feck = im;
    for (int i = 0; i < num_threads; ++i) {
        threads_id[i] = i;
    }
    for (int i = 0; i < num_threads; ++i)
        pthread_create(&(threads[i]), NULL, threadFunction, &(threads_id[i]));
    for (int i = 0; i < num_threads; ++i)
        pthread_join(threads[i], NULL);
}

void writeData(const char * fileName, image *img) {
    FILE *output = fopen(fileName, "wb");
    fprintf(output, "P%d\n%d %d\n%d\n", img->type, img->width, img->height, img->max_value);
    for (int i = 0; i < img->width; ++i) {
        for (int j = 0; j < img->height; ++j) {
            fwrite(&img->matrix[i][j], sizeof(unsigned char), 1, output);
        }
    }
    for (int i = 0; i < img->height; ++i) {
        free(img->matrix[i]);
    }
    free(img->matrix);
    
    fclose(output);
}

