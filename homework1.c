#include "homework1.h"

int num_threads;
int resolution;

int max = 100;

pthread_t threads[8];
int threads_id[8];

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

image *feck;

int calculateDistance(int i, int j) {
    return abs((-1) * i + 2 * j) / sqrt(1 + 4);
}

void *threadFunction (void *var) {
    int tid = *(int *) var;
   
}

void render(image *im) {

	for (int i = 0; i < resolution; i++) {
		for (int j = 0; j < resolution; j++) {
            
			float sum = (-1 * ((j + 0.5) * 100.0 / resolution)) 
                        + (2 * ((resolution - 1 - (i + 0.5)) * 100.0 / resolution));
			float distance = abs(sum) / sqrt(5);
			if(abs((-1 * ((j + 0.5f) * 100.0f / (float)resolution)) + (2 * (((float)resolution - 1 - (i - 0.5f)) * 100.0F / resolution))) / sqrt(5) <= 3.0f) {
				im->matrix[i][j] = 0;
			}
		}
	} 
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

