#include "helpers.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    int averageR;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //average each pixell
            average = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            average /= 3;
            //round it
            averageR = roundf(average);
            //change
            image[i][j].rgbtRed = averageR;
            image[i][j].rgbtGreen = averageR;
            image[i][j].rgbtBlue = averageR;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculate sepia for each pixel
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            //cap it at 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            //change
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        //only do half
        for (int j = 0; j < width / 2; j++)
        {
            //swap
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;

        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float blurRed, blurBlue, blurGreen;
    int blurRedR, blurBlueR, blurGreenR;
    int counter = 0;
    RGBTRIPLE imageC [height][width];
    //copy image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageC[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //the pixel
            blurRed = imageC[i][j].rgbtRed;
            blurGreen = imageC[i][j].rgbtGreen;
            blurBlue = imageC[i][j].rgbtBlue;
            counter++;
            //to the left
            if (j != 0)
            {
                blurRed = blurRed + imageC[i][j - 1].rgbtRed;
                blurGreen = blurGreen + imageC[i][j - 1].rgbtGreen;
                blurBlue = blurBlue + imageC[i][j - 1].rgbtBlue;
                counter++;
            }
            //to the right
            if (j != width - 1)
            {
                blurRed = blurRed + imageC[i][j + 1].rgbtRed;
                blurGreen =  blurGreen + imageC[i][j + 1].rgbtGreen;
                blurBlue = blurBlue + imageC[i][j + 1].rgbtBlue;
                counter++;
            }
            //above
            if (i != 0)
            {
                blurRed = blurRed + imageC[i - 1][j].rgbtRed;
                blurGreen = blurGreen + imageC[i - 1][j].rgbtGreen;
                blurBlue = blurBlue + imageC[i - 1][j].rgbtBlue;
                counter++;
            }
            //below
            if (i != height - 1)
            {
                blurRed = blurRed + imageC[i + 1][j].rgbtRed;
                blurGreen = blurGreen + imageC[i + 1][j].rgbtGreen;
                blurBlue = blurBlue + imageC[i + 1][j].rgbtBlue;
                counter++;
            }
            //top left
            if (i != 0 && j != 0)
            {
                blurRed = blurRed + imageC[i - 1][j - 1].rgbtRed;
                blurGreen = blurGreen + imageC[i - 1][j - 1].rgbtGreen;
                blurBlue = blurBlue + imageC[i - 1][j - 1].rgbtBlue;
                counter++;
            }
            //top right
            if (i != 0 && j != width - 1)
            {
                blurRed = blurRed + imageC[i - 1][j + 1].rgbtRed;
                blurGreen = blurGreen + imageC[i - 1][j + 1].rgbtGreen;
                blurBlue = blurBlue + imageC[i - 1][j + 1].rgbtBlue;
                counter++;
            }
            //bottom right
            if (i != height - 1 && j != width - 1)
            {
                blurRed = blurRed + imageC[i + 1][j + 1].rgbtRed;
                blurGreen = blurGreen + imageC[i + 1][j + 1].rgbtGreen;
                blurBlue = blurBlue + imageC[i + 1][j + 1].rgbtBlue;
                counter++;
            }
            //bottom left
            if (i != height - 1 && j != 0)
            {
                blurRed = blurRed + imageC[i + 1][j - 1].rgbtRed;
                blurGreen = blurGreen + imageC[i + 1][j - 1].rgbtGreen;
                blurBlue = blurBlue + imageC[i + 1][j - 1].rgbtBlue;
                counter++;
            }
            //calculate blur
            blurRed /= counter;
            blurBlue /= counter;
            blurGreen /= counter;
            //round
            blurRedR = round(blurRed);
            blurBlueR = round(blurBlue);
            blurGreenR = round(blurGreen);
            //change
            image[i][j].rgbtRed = blurRedR;
            image[i][j].rgbtGreen = blurGreenR;
            image[i][j].rgbtBlue = blurBlueR;
            counter = 0;
        }
    }
    return;
}
