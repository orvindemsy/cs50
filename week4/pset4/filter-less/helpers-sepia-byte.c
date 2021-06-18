#include <stdio.h>
#include "helpers.h"

typedef uint8_t BYTE;

BYTE maxRGB(BYTE sepiaRGB);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Try printing height and width
    // printf("Image height: %d\n", height);
    // printf("Image width : %d\n", width);

    // printf("Red  : %d\n", image[0][0].rgbtRed);
    // printf("Blue : %d\n", image[0][0].rgbtBlue);
    // printf("Green: %d\n", image[0][0].rgbtGreen);

    BYTE convert;
    // printf("Convert: %d\n", convert);

    for (int h=0; h < height; h++){
        for (int w=0; w < width; w++){
            convert = (image[h][w].rgbtBlue + image[h][w].rgbtRed + image[h][w].rgbtGreen) / 3;
            // printf("Convert: %d\n", convert);
            image[h][w].rgbtBlue = convert;
            image[h][w].rgbtRed  = convert;
            image[h][w].rgbtGreen = convert;
        }
    }
    // printf("Success\n");
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE sepiaRed, sepiaGreen, sepiaBlue;

    for (int h=0; h < height; h++){
        for (int w=0; w < width; w++){

            // sepiaRed   = (int) maxRGB(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            // sepiaGreen = (int) maxRGB(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            // sepiaBlue  = (int) maxRGB(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);

            sepiaRed   = maxRGB((BYTE) .393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            sepiaGreen = maxRGB((BYTE) .349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            sepiaBlue  = maxRGB((BYTE) .272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);

            // sepiaRed   = maxRGB(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            // sepiaGreen = maxRGB(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            // sepiaBlue  = maxRGB(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);


            // if (sepiaRed > 255){
            //     printf("Sepia Red: %d\n", sepiaRed);
            //     printf("max red\n");
            //     sepiaRed   = 255;
            // }
            // if (sepiaGreen > 255){
            //     printf("Sepia Red: %d\n", sepiaGreen);
            //     printf("max green\n");
            //     sepiaGreen = 255;
            // }
            // if (sepiaBlue  > 255){
            //     printf("Sepia Red: %d\n", sepiaBlue);
            //     printf("max blue\n");
            //     sepiaBlue  = 255;
            // }

            image[h][w].rgbtRed   = sepiaRed;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtBlue  = sepiaBlue;
        }
        printf("\n");
    }
    printf("Success\n");
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Helper funtion for sephia
BYTE maxRGB(BYTE sepiaRGB){
    if (sepiaRGB > (BYTE) 255){
        return (BYTE) 255;
    }

    return sepiaRGB;
}