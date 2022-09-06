#include "helpers.h"
#include <math.h>
#include <stdio.h>
int cap255(double n);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float rGx, gGx, bGx, rGy, gGy, bGy;
            rGx = gGx = bGx = rGy = gGy = bGy = 0;
            //find value of the surrounding pixels

            //left
            if (j > 0)
            {

                rGx += image[i][j - 1].rgbtRed * -2;
                gGx += image[i][j - 1].rgbtGreen * -2;
                bGx += image[i][j - 1].rgbtBlue * -2;
            }
            //right
            if (j < width - 1)
            {

                rGx += image[i][j + 1].rgbtRed * 2;
                gGx += image[i][j + 1].rgbtGreen * 2;
                bGx += image[i][j + 1].rgbtBlue * 2;
            }
            //above
            if (i > 0)
            {
                rGy += image[i - 1][j].rgbtRed * -2;
                gGy += image[i - 1][j].rgbtGreen * -2;
                bGy += image[i - 1][j].rgbtBlue * -2;
            }
            //below
            if (i < height - 1)
            {
                rGy += image[i + 1][j].rgbtRed * 2;
                gGy += image[i + 1][j].rgbtGreen * 2;
                bGy += image[i + 1][j].rgbtBlue * 2;
            }
            //top left
            if (i > 0 && j > 0)
            {

                rGx += image[i - 1][j - 1].rgbtRed * -1;
                gGx += image[i - 1][j - 1].rgbtGreen * -1;
                bGx += image[i - 1][j - 1].rgbtBlue * -1;

                rGy += image[i - 1][j - 1].rgbtRed * -1;
                gGy += image[i - 1][j - 1].rgbtGreen * -1;
                bGy += image[i - 1][j - 1].rgbtBlue * -1;
            }
            //top right
            if (i > 0 && j < width - 1)
            {

                rGx += image[i - 1][j + 1].rgbtRed * 1;
                gGx += image[i - 1][j + 1].rgbtGreen * 1;
                bGx += image[i - 1][j + 1].rgbtBlue * 1;

                rGy += image[i - 1][j + 1].rgbtRed * -1;
                gGy += image[i - 1][j + 1].rgbtGreen * -1;
                bGy += image[i - 1][j + 1].rgbtBlue * -1;
            }
            //bottom right
            if (i < height - 1 && j < width - 1)
            {

                rGx += image[i + 1][j + 1].rgbtRed * 1;
                gGx += image[i + 1][j + 1].rgbtGreen * 1;
                bGx += image[i + 1][j + 1].rgbtBlue * 1;

                rGy += image[i + 1][j + 1].rgbtRed * 1;
                gGy += image[i + 1][j + 1].rgbtGreen * 1;
                bGy += image[i + 1][j + 1].rgbtBlue * 1;
            }
            //bottom left
            if (i < height - 1 && j > 0)
            {

                rGx += image[i + 1][j - 1].rgbtRed * -1;
                gGx += image[i + 1][j - 1].rgbtGreen * -1;
                bGx += image[i + 1][j - 1].rgbtBlue * -1;

                rGy += image[i + 1][j - 1].rgbtRed * 1;
                gGy += image[i + 1][j - 1].rgbtGreen * 1;
                bGy += image[i + 1][j - 1].rgbtBlue * 1;
            }

            //round
            int red = round(sqrt((rGx * rGx) + (rGy * rGy)));
            int green = round(sqrt((gGx * gGx) + (gGy * gGy)));
            int blue = round(sqrt((bGx * bGx) + (bGy * bGy)));
            //cap
            if (red > 255)
            {
                red = 255;
            }
            else if (red < 0)
            {
                red = 0;
            }
            if (green > 255)
            {
                green = 255;
            }
            else if (green < 0)
            {
                green = 0;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            else if (blue < 0)
            {
                blue = 0;
            }

            //change
            copy[i][j].rgbtRed = red;
            copy[i][j].rgbtGreen = green;
            copy[i][j].rgbtBlue = blue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
    return;

}
