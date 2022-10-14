#include "helpers.h"
#include "stdio.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // height: 400
    // width: 600
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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // height: 400
    // width: 600
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE auxImage[height][width];

    for (int a = 0; a < height; a++)
    {
        for (int l = 0; l < width; l++)
        {
            auxImage[a][l] = image[a][l];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE Gx[9];

            for (int k = 0; k < 9; k++)
            {
                Gx[k].rgbtBlue = 0;
                Gx[k].rgbtGreen = 0;
                Gx[k].rgbtRed = 0;
            }

            if ((i - 1) >= 0)
            {
                if ((j - 1) >= 0)
                {
                    Gx[0] = auxImage[i - 1][j - 1]; // 0, 0
                }
                if ((j + 1) <= (width - 1))
                {
                    Gx[2] = auxImage[i - 1][j + 1]; // 0, 2

                }
                Gx[1] = auxImage[i - 1][j]; // 0, 1

            }

            if ((j - 1) >= 0)
            {
                Gx[3] = auxImage[i][j - 1]; // 1, 0
            }

            Gx[4] = auxImage[i][j]; // 1, 1

            if ((j + 1) <= (width - 1))
            {
                Gx[5] = auxImage[i][j + 1]; // 1, 2
            }

            if ((i + 1) <= (height - 1))
            {
                if ((j - 1) >= 0)
                {
                    Gx[6] = auxImage[i + 1][j - 1]; // 2, 0

                }
                if ((j + 1) <= (width - 1))
                {
                    Gx[8] = auxImage[i + 1][j + 1]; // 2, 2

                }
                Gx[7] = auxImage[i + 1][j]; // 2, 1

            }

            double sumGxBlue = 0.0;
            double sumGxGreen = 0.0;
            double sumGxRed = 0.0;

            for (int g = 0; g < 9; g++)
            {
                if (g == 0 || g == 6)
                {
                    sumGxBlue += (Gx[g].rgbtBlue * -1.0);
                    sumGxGreen += (Gx[g].rgbtGreen * -1.0);
                    sumGxRed += (Gx[g].rgbtRed * -1.0);
                }
                else if (g == 3)
                {
                    sumGxBlue += (Gx[g].rgbtBlue * -2.0);
                    sumGxGreen += (Gx[g].rgbtGreen * -2.0);
                    sumGxRed += (Gx[g].rgbtRed * -2.0);
                }
                else if (g == 5)
                {
                    sumGxBlue += (Gx[g].rgbtBlue * 2.0);
                    sumGxGreen += (Gx[g].rgbtGreen * 2.0);
                    sumGxRed += (Gx[g].rgbtRed * 2.0);
                }
                else if (g == 1 || g == 4 || g == 7)
                {
                    sumGxBlue += 0.0;
                    sumGxGreen += 0.0;
                    sumGxRed += 0.0;
                }
                else
                {
                    sumGxBlue += (double) Gx[g].rgbtBlue;
                    sumGxGreen += (double) Gx[g].rgbtGreen;
                    sumGxRed += (double) Gx[g].rgbtRed;
                }
            }

            double sumGyBlue = 0.0;
            double sumGyGreen = 0.0;
            double sumGyRed = 0.0;

            for (int b = 0; b < 9; b++)
            {
                if (b == 0 || b == 2)
                {
                    sumGyBlue += (Gx[b].rgbtBlue * -1.0);
                    sumGyGreen += (Gx[b].rgbtGreen * -1.0);
                    sumGyRed += (Gx[b].rgbtRed * -1.0);
                }
                else if (b == 1)
                {
                    sumGyBlue += (Gx[b].rgbtBlue * -2.0);
                    sumGyGreen += (Gx[b].rgbtGreen * -2.0);
                    sumGyRed += (Gx[b].rgbtRed * -2.0);
                }
                else if (b == 7)
                {
                    sumGyBlue += (Gx[b].rgbtBlue * 2.0);
                    sumGyGreen += (Gx[b].rgbtGreen * 2.0);
                    sumGyRed += (Gx[b].rgbtRed * 2.0);
                }
                else if (b == 3 || b == 4 || b == 5)
                {
                    sumGyBlue += 0.0;
                    sumGyGreen += 0.0;
                    sumGyRed += 0.0;
                }
                else
                {
                    sumGyBlue += (double) Gx[b].rgbtBlue;
                    sumGyGreen += (double) Gx[b].rgbtGreen;
                    sumGyRed += (double) Gx[b].rgbtRed;
                }
            }

            double sumBlue = sqrt((sumGxBlue * sumGxBlue) + (sumGyBlue * sumGyBlue));
            double sumGreen = sqrt((sumGxGreen * sumGxGreen) + (sumGyGreen * sumGyGreen));
            double sumRed = sqrt((sumGxRed * sumGxRed) + (sumGyRed * sumGyRed));

            if (sumBlue > 255)
            {
                sumBlue = 255.0;
            }
            if (sumGreen > 255)
            {
                sumGreen = 255.0;
            }
            if (sumRed > 255)
            {
                sumRed = 255.0;
            }

            image[i][j].rgbtBlue = (int) round(sumBlue);
            image[i][j].rgbtGreen = (int) round(sumGreen);
            image[i][j].rgbtRed = (int) round(sumRed);
        }
    }
    return;
}