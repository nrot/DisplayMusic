#include <stdio.h>
#include <math.h>
#include <aquila/source/WaveFile.h>
#include "examples/ampl_view.h"
#include <gd.h>

using namespace std;

int main(int argc, char** argv)
{
  
    char name_file[] = "/home/nrot/OpenCVTutor/File_1.wav";
    /*char *name_file;
    if (argc>1) name_file = argv[1];
    else {
        printf("Pls File.wav\n");
        return -1;
    }*/
    Aquila::WaveFile wave(name_file);

    FILE *png_out;
    gdImagePtr im = Koch_snow_flake(wave);

    if (argc>2) png_out = fopen(argv[2], "wb"); else png_out = fopen("test.png", "wb");
    gdImagePng(im, png_out);
    fclose(png_out);

    gdImageDestroy(im);

    return 0;
}
