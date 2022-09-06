#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    //open that file
    FILE *file = fopen(argv[1], "r");
    //if it cant error
    if (file == NULL)
    {
        printf("Cannot open: %s\n", argv[1]);
        return 1;
    }
    //array to store bytes
    BYTE buffer[512];
    //counter of images
    int counter = 0;
    //name of jpg
    char filename[8];
    //new image file
    FILE *img = NULL;
    //is there an active file
    bool isopen = false;

    while (true)
    {
        //read block
        int bytesread = fread(buffer, 1, 512, file);
        //if nothing was read and end of file end
        if (bytesread == 0 && feof(file))
        {
            break;
        }
        //if starts as jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if active file close it
            if (isopen == true)
            {
                fclose(img);
            }
            else
            {
                isopen = true;
            }
            //open new file
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter++;
        }
        //write the bytes to new image
        if (img != NULL)
        {
            fwrite(buffer, 1, bytesread, img);
        }
    }
    //close files
    fclose(file);
    fclose(img);
}
