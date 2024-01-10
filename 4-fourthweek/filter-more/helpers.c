#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            // without (j + 1), the first vertical line stays the same
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue = 0;
            float green = 0;
            float red = 0;
            float count = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k >= 0 && i + k <= height - 1) && (j + l >= 0 && j + l <= width - 1))
                    {
                        blue += image[i + k][j + l].rgbtBlue;
                        green += image[i + k][j + l].rgbtGreen;
                        red += image[i + k][j + l].rgbtRed;
                        count++;
                    }
                }
            }

            image[i][j].rgbtBlue = round(blue / count);
            image[i][j].rgbtGreen = round(green / count);
            image[i][j].rgbtRed = round(red / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // temp 2d array to copy all pixels without bugs in the image 2d array
    RGBTRIPLE temp[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxRed = 0;
            int gxGreen = 0;
            int gxBlue = 0;
            int gyRed = 0;
            int gyGreen = 0;
            int gyBlue = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k >= 0 && i + k <= height - 1) && (j + l >= 0 && j + l <= width - 1))
                    {
                        gxBlue += image[i + k][j + l].rgbtBlue * gx[k + 1][l + 1];
                        gxGreen += image[i + k][j + l].rgbtGreen * gx[k + 1][l + 1];
                        gxRed += image[i + k][j + l].rgbtRed * gx[k + 1][l + 1];
                        gyBlue += image[i + k][j + l].rgbtBlue * gy[k + 1][l + 1];
                        gyGreen += image[i + k][j + l].rgbtGreen * gy[k + 1][l + 1];
                        gyRed += image[i + k][j + l].rgbtRed * gy[k + 1][l + 1];
                    }
                }
            }
            int blue = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));
            int green = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            int red = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            
            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}
