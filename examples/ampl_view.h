//
// Created by nrot on 11.11.16.
//

#ifndef DISPLAYMUSIC_AMPL_VIEW_H
#define DISPLAYMUSIC_AMPL_VIEW_H

#endif //DISPLAYMUSIC_AMPL_VIEW_H

#include <gd.h>
#include <aquila/source/WaveFile.h>
#include "../classes/coords.h"
#include "../classes/line.h"

gdImagePtr view_1(Aquila::WaveFile wave);
gdImagePtr Koch_snow_flake(Aquila::WaveFile wave);
void Koch_snow_flake_draw_step(gdImagePtr im, Aquila::SampleType *heights, coords a, coords e, int t0, int t1, int deep, double angel);
coords coords_from_part(double length, double factor, double angel);