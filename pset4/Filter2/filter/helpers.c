#include "helpers.h"
#include "stdio.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            double average = round((blue + green + red) / 3.0);

            image[i][j].rgbtBlue = (int) average;
            image[i][j].rgbtGreen = (int) average;
            image[i][j].rgbtRed = (int) average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            double sepiaRed = (0.393 * red) + (0.769 * green) + (0.189 * blue);
            double sepiaGreen = (0.349 * red) + (0.686 * green) + (0.168 * blue);
            double sepiaBlue = (0.272 * red) + (0.534 * green) + (0.131 * blue);

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255.0;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255.0;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255.0;
            }

            image[i][j].rgbtBlue = (int) round(sepiaBlue);
            image[i][j].rgbtGreen = (int) round(sepiaGreen);
            image[i][j].rgbtRed = (int) round(sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int averageWidth = width / 2; // 300
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < averageWidth; j++)
        {
            RGBTRIPLE aux = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = aux;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE auxImage[height][width];

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            auxImage[a][b] = image[a][b];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE aux[9];
            double auxCount = 0.0;
            for (int k = 0; k < 9; k++)
            {
                aux[k].rgbtBlue = 0;
                aux[k].rgbtGreen = 0;
                aux[k].rgbtRed = 0;
            }

            if ((i - 1) >= 0)
            {
                if ((j - 1) >= 0)
                {
                    aux[0] = auxImage[i - 1][j - 1]; // 0, 0
                    auxCount++;
                }
                if ((j + 1) <= (width - 1))
                {
                    aux[2] = auxImage[i - 1][j + 1]; // 0, 2
                    auxCount++;
                }
                aux[1] = auxImage[i - 1][j]; // 0, 1
                auxCount++;
            }

            if ((j - 1) >= 0)
            {
                aux[3] = auxImage[i][j - 1]; // 1, 0
                auxCount++;
            }

            aux[4] = auxImage[i][j]; // 1, 1
            auxCount++;

            if ((j + 1) <= (width - 1))
            {
                aux[5] = auxImage[i][j + 1]; // 1, 2
                auxCount++;
            }

            if ((i + 1) <= (height - 1))
            {
                if ((j - 1) >= 0)
                {
                    aux[6] = auxImage[i + 1][j - 1]; // 2, 0
                    auxCount++;
                }
                if ((j + 1) <= (width - 1))
                {
                    aux[8] = auxImage[i + 1][j + 1]; // 2, 2
                    auxCount++;
                }
                aux[7] = auxImage[i + 1][j]; // 2, 1
                auxCount++;
            }

            int averageRgbtBlue = 0;
            int averageRgbtGreen = 0;
            int averageRgbtRed = 0;

            for (int g = 0; g < 9; g++)
            {
                averageRgbtBlue += aux[g].rgbtBlue;
                averageRgbtGreen += aux[g].rgbtGreen;
                averageRgbtRed += aux[g].rgbtRed;
            }

            double auxBlue = round(averageRgbtBlue / (double) auxCount);
            double auxGreen = round(averageRgbtGreen / (double) auxCount);
            double auxRed = round(averageRgbtRed / (double) auxCount);

            image[i][j].rgbtBlue = (int) auxBlue;
            image[i][j].rgbtGreen = (int) auxGreen;
            image[i][j].rgbtRed = (int) auxRed;
        }
    }
    return;
}
