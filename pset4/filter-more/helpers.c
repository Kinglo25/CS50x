#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    int r, g, b;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            r = image[i][j].rgbtRed;
            g = image[i][j].rgbtGreen;
            b = image[i][j].rgbtBlue;
            average = round((r + g + b) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

//swap fct
void    swap(BYTE *a, BYTE *b)
{
    BYTE tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j].rgbtRed, &image[i][width - j - 1].rgbtRed);
            swap(&image[i][j].rgbtGreen, &image[i][width - j - 1].rgbtGreen);
            swap(&image[i][j].rgbtBlue, &image[i][width - j - 1].rgbtBlue);
        }
    }
    return;
}

//Checks if we are in the image
int is_in(int height, int width, int i, int j)
{
    return (i >= 0 && i < height && j >= 0 && j < width);
}

void blur_pixel(int height, int width, int i, int j, RGBTRIPLE image[height][width], RGBTRIPLE tmp_image[height][width])
{
    float averageRed = 0, averageGreen = 0, averageBlue = 0;
    float count = 0;

    for (int k = -1; k <= 1; k++)
    {
        for (int l = -1; l <= 1; l++)
        {
            if (is_in(height, width, i + k, j + l))
            {
                averageRed += image[i + k][j + l].rgbtRed;
                averageGreen += image[i + k][j + l].rgbtGreen;
                averageBlue += image[i + k][j + l].rgbtBlue;
                count++;
            }
        }
    }
    //Creates a new image with the average values
    tmp_image[i][j].rgbtRed = round(averageRed / count);
    tmp_image[i][j].rgbtGreen = round(averageGreen / count);
    tmp_image[i][j].rgbtBlue = round(averageBlue / count);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];

    //Goes through each pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blur_pixel(height, width, i, j, image, tmp_image);
        }
    }
    //Copy the image with the new image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp_image[i][j].rgbtBlue;
        }
    }
    return;
}

void    kernel_pixel(int height, int width, int i, int j, RGBTRIPLE image[height][width], RGBTRIPLE tmp_image[height][width])
{
    int sobel_op[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    float GxRed = 0, GxGreen = 0, GxBlue = 0, GyRed = 0, GyGreen = 0, GyBlue = 0;
    int gRed = 0, gGreen = 0, gBlue = 0;

    //Apply Sobel operator to each grid of pixel in the x dir
    for (int k = -1; k <= 1; k++)
    {
        for (int l = -1; l <= 1; l++)
        {
            if (is_in(height, width, i + k, j + l))
            {
                GxRed += (image[i + k][j + l].rgbtRed * sobel_op[k + 1][l + 1]);
                GxGreen += (image[i + k][j + l].rgbtGreen * sobel_op[k + 1][l + 1]);
                GxBlue += (image[i + k][j + l].rgbtBlue * sobel_op[k + 1][l + 1]);
            }
        }
    }
    //Apply Sobel operator to each grid of pixel in the y dir
    for (int k = -1; k <= 1; k++)
    {
        for (int l = -1; l <= 1; l++)
        {
            if (is_in(height, width, i + k, j + l))
            {
                GyRed += (image[i + k][j + l].rgbtRed * sobel_op[l + 1][k + 1]);
                GyGreen += (image[i + k][j + l].rgbtGreen * sobel_op[l + 1][k + 1]);
                GyBlue += (image[i + k][j + l].rgbtBlue * sobel_op[l + 1][k + 1]);
            }
        }
    }
    //check final value to cap it at 255
    if ((gRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)))) > 255)
        gRed = 255;
    if ((gGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)))) > 255)
        gGreen = 255;
    if ((gBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)))) > 255)
       gBlue = 255;
    //Creates a new image with the final values
    tmp_image[i][j].rgbtRed = gRed;
    tmp_image[i][j].rgbtGreen = gGreen;
    tmp_image[i][j].rgbtBlue = gBlue;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];

    //Goes through each pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            kernel_pixel(height, width, i, j, image, tmp_image);
        }
    }
    //Copy the image with the new image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp_image[i][j].rgbtBlue;
        }
    }
    return;
}
