//
// Created by nrot on 12.11.16.
//

#include "../apps/apps_wave_file.h"
#include "../apps/apps_arrays.h"

#include <gd.h>
#include <aquila/source/WaveFile.h>

gdImagePtr view_1(Aquila::WaveFile wave)
{
    //printf("file name = %s\n", wave.getFilename());
    printf("length = %d\n", wave.getAudioLength());
    printf("length = %f seconds\n", (float)wave.getAudioLength()/1000);
    printf("length = %f minuts\n", (float)wave.getAudioLength()/60000);
    printf("samples = %d\n", (int)wave.getSamplesCount());
    //printf("max_ampl = %lu\n", max_amplitude_index(wave));
    printf("max_ampl = %lf\n", max_amplitude(wave));
    printf("min_ampl = %lf\n", min_amplitude(wave));
    printf("GHz = %lf\n", wave.getSampleFrequency());

    int IMAGE_SIZE_WIDTH = 2048;
    int IMAGE_SIZE_HEIGHT = IMAGE_SIZE_WIDTH/2;

    //Aquila::FrequencyType image_frequency = wave.getSampleFrequency()/2;
    Aquila::FrequencyType image_frequency = wave.getSamplesCount()/IMAGE_SIZE_WIDTH;
    double image_scale_height = 2*IMAGE_SIZE_HEIGHT/max_amplitude(wave);
    Aquila::SampleType *medium_ampl = medium_apmlitude_array(wave, image_frequency);

    gdImagePtr im;
    int black, white, blue;

    im = gdImageCreate(IMAGE_SIZE_WIDTH, IMAGE_SIZE_HEIGHT);

    black = gdImageColorAllocate(im, 0, 0, 0);
    white = gdImageColorAllocate(im, 255, 255, 255);
    blue = gdImageColorAllocate(im, 10, 10, 150);

    gdImageFilledRectangle(im, 0, 0, IMAGE_SIZE_WIDTH, IMAGE_SIZE_HEIGHT, white);
    int image_null = IMAGE_SIZE_HEIGHT/2;
    int y1 = 0, y2 = 0;
    for(int i=0; i<len(medium_ampl); i++)
    {
        y1 = (int) (image_null - medium_ampl[i] * image_scale_height);
        y2 = (int) (image_null + medium_ampl[i] * image_scale_height);
        gdImageLine(im, i, y1, i, y2, blue);
    }
    return im;
}