#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s!\n", argv[1]);
        return 2;
    }

    // Create a buffer for a block of data
    uint8_t buffer[BLOCK_SIZE];

    char filename[9];
    FILE *imgFile = NULL;
    int jpeg_count = 0;

    // Read 512-byte blocks until the end of the memory card
    while (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, card) > 0)
    {
        // If block indicates start of a new JPEG, open a new file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (imgFile != NULL)
            {
                fclose(imgFile);
            }

            // Open a jpeg file
            sprintf(filename, "%03i.jpg", jpeg_count);
            imgFile = fopen(filename, "w");

            // Check if any error exist while opening the file
            if (imgFile == NULL)
            {
                fclose(card);
                printf("Could not create %s\n", filename);
                return 3;
            }

            // Increase the counter
            jpeg_count++;
        }

        if (imgFile != NULL)
        {
            // If a JPEG file is currently open, write the block to it
            fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, imgFile);
        }
    }

    if (imgFile != NULL)
    {
        fclose(imgFile);
    }

    fclose(card);
    return 0;
}
