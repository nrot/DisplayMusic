//
// Created by nrot on 12.11.16.
//

#include "../apps/apps_wave_file.h"
#include "../apps/apps_arrays.h"
#include "../classes/coords.h"
#include "../classes/line.h"

#include <iostream>
#include <math.h>
#include <gd.h>
#include <aquila/source/WaveFile.h>

using namespace std;

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

coords coords_from_part(double length, double factor, double angel)
{
    coords result;
    result.x = (int)(length*factor*cos(angel));
    result.y = (int)(length*factor*sin(angel));
    return result;
}

void Koch_snow_flake_draw_step(gdImagePtr im, Aquila::SampleType *heights, coords a, coords e, int t0, int t1, int deep, double angel)
{
    //       C
    //      / \
    // A---B   D---E
    //printf("a.x = %d; a.y = %d;\ne.x = %d; e.y = %d\n", a.x, a.y, e.x, e.y);
    if(deep>4) return;
    double heights_scale;
    double now_height = heights[t0 + (t1-t0)/2];
    deep==0 ? heights_scale = 1: heights_scale = 1./pow(2, deep);
    now_height *= heights_scale;
    //printf("now_height = %f\n", now_height);
    int black = gdImageColorAllocate(im, 0, 0, 0);
    if(heights_scale*now_height < 3)
    {
        gdImageLine(im, a.x, a.y, e.x, e.y, black);
        return;
    }
    coords b,c,d;
    line ae = line(a, e);
    b = coords_from_part(ae.getLenght(), 1./3., angel);
    d = coords_from_part(ae.getLenght(), 2./3., angel);
    double new_angel = atan(now_height*2/ae.getLenght());
    new_angel = now_height<0 ? angel-new_angel: angel+new_angel;
    c = coords_from_part(ae.getLenght(), 1./2., new_angel);
    printf("                  %.4d|%.4d      \n", c.x, c.y);
    printf("                  /      \\\n");
    printf("%.4d|%.4d---%.4d|%.4d   %.4d|%.4d---%.4d|%.4d\n\n",a.x, a.y, b.x, b.y, d.x, d.y, e.x, e.y);
    Koch_snow_flake_draw_step(im, heights, a, b, t0, t0+(t1-t0)/4, ++deep, new_angel);
    Koch_snow_flake_draw_step(im, heights, b, c, t0+(t1-t0)/4, t0+(t1-t0)/2, ++deep, new_angel);
    Koch_snow_flake_draw_step(im, heights, c, d, t0+(t1-t0)/2, t0+(t1-t0)*3/4, ++deep, new_angel);
    Koch_snow_flake_draw_step(im, heights, d, e, t0+(t1-t0)*3/4, t1, ++deep, new_angel);
}

gdImagePtr Koch_snow_flake(Aquila::WaveFile wave)
{

    printf("Start\n");
    int IMAGE_SIZE_WIDTH = 2048;
    int IMAGE_SIZE_HEIGHT = IMAGE_SIZE_WIDTH/2;

    //Aquila::FrequencyType image_frequency = wave.getSampleFrequency()/2;
    Aquila::FrequencyType image_frequency = wave.getSamplesCount()/IMAGE_SIZE_WIDTH;
    double image_scale_height = 2*IMAGE_SIZE_HEIGHT/max_amplitude(wave);
    Aquila::SampleType *medium_ampl = medium_apmlitude_array(wave, image_frequency);
    unsigned int len_medium_ampl = len(medium_ampl);
    for(int i=0; i<len_medium_ampl; i++) medium_ampl[i] *= image_scale_height;

    gdImagePtr im;
    int white, blue;

    im = gdImageCreate(IMAGE_SIZE_WIDTH, IMAGE_SIZE_HEIGHT);

    white = gdImageColorAllocate(im, 255, 255, 255);
    blue = gdImageColorAllocate(im, 10, 10, 150);

    gdImageFilledRectangle(im, 0, 0, IMAGE_SIZE_WIDTH, IMAGE_SIZE_HEIGHT, white);

    coords A, E;
    A.y = E.y = IMAGE_SIZE_HEIGHT/2;
    A.x = 0; E.x = IMAGE_SIZE_WIDTH;

    Koch_snow_flake_draw_step(im, medium_ampl, A, E, 0, len_medium_ampl, 0, 0.1);
}