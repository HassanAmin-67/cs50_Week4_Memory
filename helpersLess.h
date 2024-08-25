#ifndef HELPERS_H
#define HELPERS_H

#include <math.h>
#include "bmp.h" // Assuming bmp.h defines RGBTRIPLE

// Function prototypes
void grayscale(int height, int width, RGBTRIPLE image[height][width]);
void sepia(int height, int width, RGBTRIPLE image[height][width]);
void reflect(int height, int width, RGBTRIPLE image[height][width]);
void blur(int height, int width, RGBTRIPLE image[height][width]);

#endif // HELPERS_H
