#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

bool isJPEG(uint8_t array[]);

int imageSize = 512;
int main(int argc, char *argv[])
{
    //accept single command line argument
    if( argc != 2)
    {
        printf("Usage: ./recover.c FILE.jpg.\n");
        return 1;
    }
    //open the memory card
    FILE *card = fopen(argv[1], "r");

    //check if files were opened properly
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }
    //create buffer
    uint8_t buffer[imageSize];
    //initialize counter, filename, and image
    int counter = 0;
    char filename[8];
    FILE *img = NULL;
    //LOOP: White there is still data left on the memory card:
    while(fread(buffer, 1, imageSize, card) == 512)
    {
        //look for the beginning of a jpeg
        if (isJPEG(buffer))
        {
            //check if image isn't NULL, and close image file before opening new one
            if (img != NULL)
            {
                fclose(img);
            }
        //open a new jpeg image file
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            if (img != NULL)
            {
                fwrite(buffer, 1, 512, img);
            }
            counter++;
        }
        //if not at the beginning of a jpeg
        else
        {
            if (img != NULL)
            {
                fwrite(buffer, 1, 512, img);
            }
        }
    }
    fclose(img);
    fclose(card);
}

//function to check if an image is a JPEG
bool isJPEG(uint8_t array[])
{
    if(array[0] == 0xff && array[1] == 0xd8 && array[2] ==0xff && (array[3] & 0xf0) == 0xe0 )
    {
        return true;
    }
    else
    {
        return false;
    }

}

// keep track of how many jpeg
        //open a new jpeg file
            //print an integer with three digits and sub in last parameter (make i?)
            //sprintf(filename, "%03i.jpg", 2)
            // open new file with that file name
            // FILE *img = fopen(filename, "w")
        //fwrite(buffer, 1 , imageSize, img) put this in a loop write data until we reach the end of the file
        //write 512 bytes until a new jpeg is found

        //close old one
        //start new one



    //when you find an image:
        // if cannot be opened, inform user and return 1
        //if can be opened, open and write into new file ###.jpg and loop back
        //  else if(counter != 0)
          //  {
             //   sprintf(filename, "%03i.jpg", counter);
             //   img = fopen(filename, "w");
             //   if (img != NULL)
              //  {
              //      fwrite(buffer, 1, 512, img);
              //  }
             //   counter++;
         //   }
