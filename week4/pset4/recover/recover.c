#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int CHUNK = 512;
typedef uint8_t BYTE;
int isimage(BYTE buffer[]);

int main(int argc, char *argv[])
{
    // Sanity check
    if (argc != 2){
        printf("Usage ./recover image\n");
        return 1;
    }

    // Open memory file
    FILE *input = fopen(argv[1], "r");

    if (input == NULL){
        printf("Memory cannot be open for reading\n");
        return 1;
    }

    // Necessary variable
    BYTE buffer[CHUNK];
    int count = 0;
    char *filename = malloc(sizeof(char)*8);
    FILE *out = NULL;

    // Read every 512 bytes from input
    while(fread(buffer, sizeof(BYTE), CHUNK, input) == CHUNK){

        // If an image
        if (isimage(buffer) == 0){

            printf("New image detected!, it's %i-th image\n", count);

            // If first image
            if (count == 0){
                printf("This is the %i-th image\n", count);

                // Create new filename and pointer to it
                sprintf(filename, "%03d.jpg", count);
                out = fopen(filename, "wb");

                // Add count and write to filename
                count += 1;
                fwrite(buffer, sizeof(BYTE), CHUNK, out);
            }

            else {
                printf("This is the %i-th image!\n", count);

                // Close the previous one
                fclose(out);

                // Create new filename and pointer to it
                sprintf(filename, "%03d.jpg", count);
                out = fopen(filename, "wb");

                // Add count and write to filename
                count += 1;
                fwrite(buffer, sizeof(BYTE), CHUNK, out);
            }

        }

        // If not an image
        else {

            // Check if previously image has been opened, append to that
            if (out){
                printf("Appending to previous image\n");
                fwrite(buffer, sizeof(BYTE), CHUNK, out);
            }
        }
    }

    // Closing file pointer and freeing memory
    fclose(input);
    fclose(out);
    free(filename);
}


int isimage(BYTE buffer[]){
    // If image is detected return 0
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0)){
        return 0;
    }

    return 1;
}