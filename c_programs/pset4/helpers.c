#include "helpers.h"
#include <math.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0;
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtRed = round(avg);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; //this is mandatory. wow, that caused a lot of problems.

    float blue = 0;
    float green = 0;
    float red = 0;
    int curr_pixels = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (i + x < 0 || i + x >= height || j + y < 0 || j + y >= width) //skips outside pixels
                    {
                        continue;
                    }
                    blue += image[i + x][j + y].rgbtBlue;
                    green += image[i + x][j + y].rgbtGreen;
                    red += image[i + x][j + y].rgbtRed;
                    curr_pixels++;
                }
            }
            temp[i][j].rgbtBlue = round((blue / curr_pixels));
            temp[i][j].rgbtGreen = round(green / curr_pixels);
            temp[i][j].rgbtRed = round((red / curr_pixels));
            curr_pixels = blue = green = red = 0;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int gX[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
    int gY[3][3] = {{-1,-2,-1}, {0,0,0}, {1,2,1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float xsums[3]  = {0,0,0};
            float ysums[3] = {0,0,0};

            for (int x = -1; x <= 1; x++) //fill up neighboring grid
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (i + x < 0 || i + x >= height || j + y < 0 || j + y >= width) //skips outside pixels
                    {
                        continue;
                    }
                    xsums[0] += image[i + x][j + y].rgbtBlue * gX[x+1][y+1];
                    xsums[1] += image[i + x][j + y].rgbtGreen * gX[x+1][y+1];
                    xsums[2] += image[i + x][j + y].rgbtRed * gX[x+1][y+1];

                    ysums[0] += image[i + x][j + y].rgbtBlue * gY[x+1][y+1];
                    ysums[1] += image[i + x][j + y].rgbtGreen * gY[x+1][y+1];
                    ysums[2] += image[i + x][j + y].rgbtRed * gY[x+1][y+1];
                }
            }

            int fin_b = round(sqrt(xsums[0]*xsums[0] + ysums[0]*ysums[0]));
            int fin_g = round(sqrt(xsums[1]*xsums[1] + ysums[1]*ysums[1]));
            int fin_r = round(sqrt(xsums[2]*xsums[2] + ysums[2]*ysums[2]));

            if (fin_b > 255)
                fin_b = 255;
            if (fin_g > 255)
                fin_g = 255;
            if (fin_r > 255)
                fin_r = 255;

            temp[i][j].rgbtBlue = fin_b;
            temp[i][j].rgbtGreen = fin_g;
            temp[i][j].rgbtRed = fin_r;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}