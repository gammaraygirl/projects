// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    //converts string from command line argument to a float we can use
    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    //Create an array of bytes to store the data from the header
    uint8_t header[HEADER_SIZE];
    //Read the 44-bit long element from input an store it in header
    fread(header, 1 , HEADER_SIZE ,input);
    // Write 44-bit long element from header into output
    fwrite(header, 1, HEADER_SIZE, output);

    // TODO: Read samples from input file and write updated data to output file
    //create buffer for a single sample
    int16_t buffer;
    while(fread(&buffer, sizeof(int16_t), 1, input))
    {
        //scale buffer by factor
        //printf("%d\n", buffer);
    buffer *= factor;
       // printf("SCALED: %d\n", buffer);
    //write updated sample to output
    fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
