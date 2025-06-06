#include "helpers.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get the original pixel color
            RGBTRIPLE original = image[i][j];

            // Calculate the average value
            int average = round((original.rgbtRed + original.rgbtGreen + original.rgbtBlue) / 3.0);

            // Set the pixel to the average value
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    // No need to return anything as the image is modified in place
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get the original pixel color
            RGBTRIPLE original = image[i][j];

            // Calculate the sepia values
            int sepiaRed = round(0.393 * original.rgbtRed + 0.769 * original.rgbtGreen + 0.189 * original.rgbtBlue);
            int sepiaGreen = round(0.349 * original.rgbtRed + 0.686 * original.rgbtGreen + 0.168 * original.rgbtBlue);
            int sepiaBlue = round(0.272 * original.rgbtRed + 0.534 * original.rgbtGreen + 0.131 * original.rgbtBlue);

            // Cap the values at 255
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
    // No need to return anything as the image is modified in place
    // The function modifies the image in place, so no return value is needed
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row of the image
    for (int i = 0; i < height; i++)
    {
        // Swap pixels in the row
        for (int j = 0; j < width / 2; j++)
        {
            // Swap the pixel at j with the pixel at width - j - 1
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    // No need to return anything as the image is modified in place
    // The function modifies the image in place, so no return value is needed
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image to store the blurred pixels
    RGBTRIPLE(*copy)[width] = malloc(height * sizeof(RGBTRIPLE[width]));
    if (copy == NULL)
    {
        fprintf(stderr, "Not enough memory to store blurred image.\n");
        return;
    }
    // Iterate over each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize variables to calculate the average color
            int redSum = 0, greenSum = 0, blueSum = 0;
            int count = 0;

            // Iterate over the surrounding pixels
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    // Calculate the coordinates of the surrounding pixel
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if the surrounding pixel is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // Add the color values to the sums
                        redSum += image[ni][nj].rgbtRed;
                        greenSum += image[ni][nj].rgbtGreen;
                        blueSum += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average color values and assign them to the copy
            copy[i][j].rgbtRed = round((float)redSum / count);
            copy[i][j].rgbtGreen = round((float)greenSum / count);
            copy[i][j].rgbtBlue = round((float)blueSum / count);
        }
    }
    // Copy the blurred pixels back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    // Free the allocated memory for the copy
    free(copy);
    // No need to return anything as the image is modified in place
    // The function modifies the image in place, so no return value is needed
}
