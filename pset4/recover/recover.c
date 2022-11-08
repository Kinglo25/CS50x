#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BUFFER_SIZE 512

int is_signature(uint8_t *buffer)
{
    return (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    if (input <= 0)
    {
        printf("Could not open file\n");
        return 2;
    }

    uint8_t buffer[BUFFER_SIZE];
    char *filename = malloc(8);
    int i = 0, r = 0;
    FILE *img;

    while (fread(buffer, sizeof(uint8_t), BUFFER_SIZE, input))
    {
        if (is_signature(buffer))
        {
            if (i == 0)
            {
                sprintf(filename, "%03i.jpg", i++);
                img = fopen(filename, "w");
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", i++);
                img = fopen(filename, "w");
            }
        }
        if (i != 0)
        {
            fwrite(buffer, sizeof(uint8_t), BUFFER_SIZE, img);
        }
    }
    free(filename);
    fclose(img);
    fclose(input);
}