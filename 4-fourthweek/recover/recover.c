#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover imageToRecoverFile\n");
        return 1;
    }
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    unsigned char buffer[512];
    int count = 0;
    FILE *outptr = NULL;
    char filename[8];

    while (fread(buffer, 512, 1, inptr) == 1)
    {
        // check if it is a JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
        && (buffer[3] & 0xf0) == 0xe0)
        {
            if (outptr != NULL)
            {
                fclose(outptr);
            }
            // create a new JPEG file
            sprintf(filename, "%03i.jpg", count);
            outptr = fopen(filename, "wb");
            count++;
        }
        if (outptr != NULL)
        {
            // write to the JPEG file
            fwrite(buffer, 512, 1, outptr);
        }
    }
    fclose(outptr);
    fclose(inptr);
    return 0;
}