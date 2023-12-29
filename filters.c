#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average =
                round(((float) image[i][j].rgbtRed + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtBlue) / 3.00);
            image[i][j].rgbtRed = image[i][j].rgbtBlue = image[i][j].rgbtGreen = average;
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
            int temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = temp;

            int temp2 = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = temp2;

            int temp3 = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = temp3;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagecopy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int temp = 0;
            int temp2 = 0;
            int temp3 = 0;
            int count = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k >= 0 && l >= 0 && k < height && l < width)
                    {
                        temp += image[k][l].rgbtGreen;
                        temp2 += image[k][l].rgbtRed;
                        temp3 += image[k][l].rgbtBlue;
                        count++;
                    }
                }
            }

            imagecopy[i][j].rgbtGreen = round((float) temp / (float) count);
            imagecopy[i][j].rgbtRed = round((float) temp2 / (float) count);
            imagecopy[i][j].rgbtBlue = round((float) temp3 / (float) count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtGreen = imagecopy[i][j].rgbtGreen;
            image[i][j].rgbtRed = imagecopy[i][j].rgbtRed;
            image[i][j].rgbtBlue = imagecopy[i][j].rgbtBlue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagecopy2[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imagecopy2[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int temp = 0;
            int temp2 = 0;
            int temp3 = 0;
            int count = 0;

            int tempgy = 0;
            int temp2gy = 0;
            int temp3gy = 0;
            int countgy = 0;

            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k >= 0 && l >= 0 && k < height && l < width)
                    {
                        int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
                        int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

                        temp2 += imagecopy2[k][l].rgbtRed * gx[k - i + 1][l - j + 1];
                        temp2gy += imagecopy2[k][l].rgbtRed * gy[k - i + 1][l - j + 1];

                        temp += imagecopy2[k][l].rgbtGreen * gx[k - i + 1][l - j + 1];
                        tempgy += imagecopy2[k][l].rgbtGreen * gy[k - i + 1][l - j + 1];

                        temp3 += imagecopy2[k][l].rgbtBlue * gx[k - i + 1][l - j + 1];

                        temp3gy += imagecopy2[k][l].rgbtBlue * gy[k - i + 1][l - j + 1];
                    }
                }
            }

            image[i][j].rgbtRed = round(sqrt(temp2 * temp2 + temp2gy * temp2gy));
            if (image[i][j].rgbtRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }

            image[i][j].rgbtGreen = round(sqrt(temp * temp + tempgy * tempgy));
            if (image[i][j].rgbtGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }

            image[i][j].rgbtBlue = round(sqrt((float) temp3 * (float) temp3 + (float) temp3gy * (float) temp3gy));

            if (image[i][j].rgbtBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }


//check!!
    /* for (int i = 0; i < height; i++)
      {
          for (int j = 0; j < width; j++)
          {
              image[i][j].rgbtGreen = imagecopy2[i][j].rgbtGreen;
              image[i][j].rgbtRed = imagecopy2[i][j].rgbtRed;
              image[i][j].rgbtBlue = imagecopy2[i][j].rgbtBlue;
          }
      }*/

    return;
}