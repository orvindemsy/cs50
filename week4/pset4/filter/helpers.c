#include <stdio.h>
#include <math.h>
#include "helpers.h"

typedef uint8_t BYTE;

// Declare helper functions
int maxRGB(int sepiaRGB);
void swap(BYTE *pos1, BYTE *pos2);
int validblur(int curr_h, int curr_w, int height, int width);
RGBTRIPLE blurbox(int h, int w, int maxh, int maxw, RGBTRIPLE image[maxh][maxw]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int convert;

    for (int h=0; h < height; h++){
        for (int w=0; w < width; w++){
            convert = round((image[h][w].rgbtBlue + image[h][w].rgbtRed + image[h][w].rgbtGreen) / 3.0);
            image[h][w].rgbtBlue  = convert;
            image[h][w].rgbtRed   = convert;
            image[h][w].rgbtGreen = convert;
        }
    }
    printf("Grayscale success\n");
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE sepiaRed, sepiaGreen, sepiaBlue;

    for (int h=0; h < height; h++){
        for (int w=0; w < width; w++){

            sepiaRed   = maxRGB(round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue));
            sepiaGreen = maxRGB(round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue));
            sepiaBlue  = maxRGB(round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue));

            image[h][w].rgbtRed   = sepiaRed;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtBlue  = sepiaBlue;
        }
    }
    printf("Sephia success\n");
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h=0; h < height; h++){
        // Initialize first and last index of each row
        int left  = 0;
        int right = width-1;

        // Swapping pixel values
        while (left < right){
            swap(&image[h][left].rgbtRed, &image[h][right].rgbtRed);
            swap(&image[h][left].rgbtGreen, &image[h][right].rgbtGreen);
            swap(&image[h][left].rgbtBlue, &image[h][right].rgbtBlue);
            left += 1;
            right -= 1;
        }
    }
    printf("Reflect success\n");
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create the new blur image
    RGBTRIPLE temp[height][width];

    // Creating blur image
    for (int h=0; h < height; h++){
        for (int w=0; w < width; w++){
            temp[h][w] = blurbox(h, w, height, width, image);
        }
    }

    // Copying blur image into original image
    for (int h=0; h < height; h++){
        for (int w=0; w < width; w++){
            image[h][w] = temp[h][w];
        }
    }
    printf("Blur success\n");
    return;
}

// Helper function for SEPHIA clip number at 255
int maxRGB(int sepiaRGB){
    if (sepiaRGB > 255){
        return 255;
    }

    return sepiaRGB;
}

// Helper function for BLUR
RGBTRIPLE blurbox(int h, int w, int height, int width, RGBTRIPLE image[height][width]){

    RGBTRIPLE blur;
    int blurRed = 0, blurGreen = 0, blurBlue = 0;
    int numvalid = 0;

    // Checking neighbor index
    for (int i = -1; i <= 1; i ++){
        for (int j = -1; j <= 1; j++){
              if (validblur(h+i, w+j, height, width) == 0){
                    numvalid += 1;
                    blurRed   += image[h+i][w+j].rgbtRed;
                    blurGreen += image[h+i][w+j].rgbtGreen;
                    blurBlue  += image[h+i][w+j].rgbtBlue;
              }
        }
    }

    // Averaging over valid values
    blur.rgbtRed   = round(blurRed   / (float) numvalid);
    blur.rgbtGreen = round(blurGreen / (float) numvalid);
    blur.rgbtBlue  = round(blurBlue  / (float) numvalid);

    return blur;
}

int validblur(int curr_h, int curr_w, int height, int width){
    // Return 0 if current h and w is valid index else -1
    if (curr_h >= 0 && curr_h < height){
        if (curr_w >= 0 && curr_w < width){
            return 0;
        }
    }
    return -1;
}

// Helper function for REFLECT; swap two position
void swap(BYTE* pos1, BYTE* pos2){
    BYTE temp;

    temp = *pos1;
    *pos1 = *pos2;
    *pos2 = temp;
}