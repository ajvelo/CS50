/**
 * A file that recovers lost JPEGs
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define BLOCK 512

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    // remember filenames
    char *infile = argv[1];
 
    // open file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    FILE* outptr;
    uint8_t buffer[512];
    int count = 0;
    
    // find lost images and write to outfile
    while (fread(buffer, BLOCK, 1, inptr))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
            && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            char filename[8];
            sprintf(filename, "%03d.jpg", count);
            outptr = fopen(filename, "w");
            count++;
            
            if (outptr == NULL)
                {
                    fclose(inptr);
                    fprintf(stderr, "Could not create %s.\n", filename);
                    return 3;
                }
        
        }
        
    if (outptr != NULL)
    {
        fwrite(&buffer, BLOCK, 1, outptr);
    }
    
    }

    fclose(outptr);
    fclose(inptr);  
 
    return 0;
 } 