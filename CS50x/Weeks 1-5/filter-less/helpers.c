#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //loop over all pixels
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //take average of RGB values
            float averageValue = (float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3;
            int roundedAverage = round(averageValue);
            //update pixel values
            image[i][j].rgbtRed = roundedAverage;
            image[i][j].rgbtGreen = roundedAverage;
            image[i][j].rgbtBlue = roundedAverage;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //loop over all pixels
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //compute sepia values
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            //check no pixel is greater than 255
            sepiaRed = (sepiaRed > 255) ? 255 : sepiaRed;
            sepiaGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            sepiaBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;

            //update pixel values
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
    //loop over all pixels
    int tmpRed, tmpGreen, tmpBlue;
    for(int i = 0; i < (height); i++)
    {
        for(int j = 0; (j < ( width/2)); j++)
        {
            tmpRed = image[i][j].rgbtRed;
            tmpGreen = image[i][j].rgbtGreen;
            tmpBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width-i-1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width-i-1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width-i-1].rgbtBlue;

            image[i][width-i-1].rgbtRed =tmpRed;
            image[i][width-i-1].rgbtGreen = tmpGreen;
            image[i][width-i-1].rgbtBlue = tmpBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE copy[height][width];
    float avgRed;
    float avgGreen;
    float avgBlue;

    //create copy of original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }

    }
    //iterate through each column and row
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //top left corner
            if (w == 0 && h ==0)
            {
                avgRed = (float)(copy[h][w].rgbtRed + copy[h + 1][w].rgbtRed  + copy[h + 1 ][w + 1].rgbtRed  + copy[h][w + 1].rgbtRed )/4;
                avgGreen = (float)(copy[h][w].rgbtGreen + copy[h + 1][w].rgbtGreen  + copy[h + 1 ][w + 1].rgbtGreen  + copy[h][w + 1].rgbtGreen )/4;
                avgBlue = (float)(copy[h][w].rgbtBlue + copy[h + 1][w].rgbtBlue  + copy[h + 1 ][w + 1].rgbtBlue  + copy[h][w + 1].rgbtBlue )/4;

                //round
                avgRed = round(avgRed);
                avgBlue = round(avgBlue);
                avgGreen = round(avgGreen);

                //update pixels
                image[h][w].rgbtRed = avgRed;
                image[h][w].rgbtBlue = avgBlue;
                image[h][w].rgbtGreen = avgGreen;
            }
            //lower left edge
           // elseif(w == 0 && h == (height - 1))
            //top right corner
           // elseif(w == (width - 1) && h == 0)
            //lower right
          //  elseif(w == (width - 1) && h == (height - 1))
            //left side
         //  else if(w == 0 && (h > 0 && h < (height - 1)))
            //right side
          //  if(w == (width - 1) && (h > 0 && h < (height - 1)))
            //upper side
         //   if((w > 0 && w < (width - 1)) && h == 0)
            //lower side
        //    if((w > 0 && w < (width - 1)) && h == (height - 1))
            //middle (can form 3x3 grid)
        //    if((w > 0 && w < (width - 1)) && ( h < 0 &&  h > (height - 1)))

        }

    }
    return;
}


  //for (int k = -1; k <= 1; k++)
      //      {
       //         for (int m = -1; m <= 1; m++)
       //         {
        //            image[i][j].rgbtRed = copy[m][k];
      //          }
        //    }
   //     }
