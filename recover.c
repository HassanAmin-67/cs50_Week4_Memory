#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define the size of a block
#define BLOCK_SIZE 512

// Define a type for a byte (since it's not available in standard C)
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Open memory card file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    // Buffer to store a block of data
    BYTE buffer[BLOCK_SIZE];

    // Track the number of images found
    int image_count = 0;

    // File pointer for the currently open JPEG
    FILE *img = NULL;

    // File name for each recovered JPEG
    char filename[8];

    // Read the memory card file block by block
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // Check if the block is the start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If an image is already open, close it
            if (img != NULL)
            {
                fclose(img);
            }

            // Create a new file for the JPEG
            sprintf(filename, "%03i.jpg", image_count);
            img = fopen(filename, "w");
            image_count++;
        }

        // If an image file is open, write the block to it
        if (img != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
    }

    // Close any remaining open files
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(file);

    return 0;
}
