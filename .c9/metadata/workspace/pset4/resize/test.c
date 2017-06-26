{"filter":false,"title":"test.c","tooltip":"/pset4/resize/test.c","undoManager":{"mark":2,"position":2,"stack":[[{"start":{"row":0,"column":0},"end":{"row":282,"column":1},"action":"insert","lines":["8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116","117","118","119","120","121","122","123","124","125","126","127","128","129","130","131","132","133","134","135","136","137","138","139","140","141","142","143","144","145","/**"," * resize.c"," *"," * Andrew Ke"," * andrewke.org"," *"," * Solution for cs50 pset4 hacker edition"," * Scales a bmp smaller and bigger (any decimal accepted)!"," */","       ","#include <stdio.h>","#include <stdlib.h>"," ","#include \"bmp.h\""," ","int main(int argc, char* argv[])","{","    // ensure proper usage","    if (argc != 4)","    {","        printf(\"Usage: ./resize n infile outfile\\n\");","        return 1;","    }"," ","    // retrieve the scaling factor as a float","    double scale = atof(argv[1]);","    ","    // remember filenames","    char* infile = argv[2];","    char* outfile = argv[3];"," ","    // open input file ","    FILE* inptr = fopen(infile, \"r\");","    if (inptr == NULL)","    {","        printf(\"Could not open %s.\\n\", infile);","        return 2;","    }"," ","    // open output file","    FILE* outptr = fopen(outfile, \"w\");","    if (outptr == NULL)","    {","        fclose(inptr);","        fprintf(stderr, \"Could not create %s.\\n\", outfile);","        return 3;","    }"," ","    // read infile's BITMAPFILEHEADER","    BITMAPFILEHEADER bf;","    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);"," ","    // read infile's BITMAPINFOHEADER","    BITMAPINFOHEADER bi;","    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);"," ","    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0","    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || ","        bi.biBitCount != 24 || bi.biCompression != 0)","    {","        fclose(outptr);","        fclose(inptr);","        fprintf(stderr, \"Unsupported file format.\\n\");","        return 4;","    }"," ","    // determine padding for scanlines (for the image we are reading from)","    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;","    ","    // an array to store all of the pixels in the image we are reading from","    RGBTRIPLE image[bi.biWidth][abs(bi.biHeight)];","    ","    // iterate over infile's scanlines","    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)","    {","        // iterate over pixels in scanline","        for (int j = 0; j < bi.biWidth; j++)","        {","            // temporary storage","            RGBTRIPLE triple;"," ","            // read RGB triple from infile","            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);","            ","            // store it in the array","            image[j][i] = triple;","        }","        ","        // skip over padding, if any","        fseek(inptr, padding, SEEK_CUR);","    }","    ","    // change the width and height measurements to suit the new scaled image","    bi.biWidth *= scale;","    bi.biHeight *= scale;","    ","    // recalculate the padding (for the sclaed image we are writing)","    padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;","    ","    // calculate the number of bytes in the non-header part of the image","    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * sizeof(RGBTRIPLE) + padding);","    ","    // calculate the total number of bytes in the image (with the headers)","    bf.bfSize = bi.biSizeImage + 54;","    ","    // write outfile's BITMAPFILEHEADER","    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);"," ","    // write outfile's BITMAPINFOHEADER","    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);","    ","    // writing to the scaled image's out file","    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)","    {","        for (int j = 0; j < bi.biWidth; j++)","        {","            // temporary storage","            RGBTRIPLE triple;","            ","            // use the scale factor to find the pixel that should be placed","            triple = image[(int) (j / scale)][(int) (i / scale)];","            ","            // printf(\"(%i, %i, %i)\\n\", triple.rgbtRed, triple.rgbtGreen, triple.rgbtBlue);","            ","            // write the pixel to the file","            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr); ","        }","        ","        // write the buffer","        for (int k = 0; k < padding; k++)","        {","            fputc(0x00, outptr);","        }","    }","    "," ","    // close infile","    fclose(inptr);"," ","    // close outfile","    fclose(outptr);"," ","    // that's all folks","    return 0;","}"],"id":1}],[{"start":{"row":0,"column":0},"end":{"row":137,"column":3},"action":"remove","lines":["8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116","117","118","119","120","121","122","123","124","125","126","127","128","129","130","131","132","133","134","135","136","137","138","139","140","141","142","143","144","145"],"id":2}],[{"start":{"row":0,"column":0},"end":{"row":1,"column":0},"action":"remove","lines":["",""],"id":3}]]},"ace":{"folds":[],"scrolltop":0,"scrollleft":0,"selection":{"start":{"row":9,"column":7},"end":{"row":9,"column":7},"isBackwards":false},"options":{"guessTabSize":true,"useWrapMode":false,"wrapToView":true},"firstLineState":0},"timestamp":1493218996014,"hash":"6c9810f6eec5f7039d4516213c78720099239151"}