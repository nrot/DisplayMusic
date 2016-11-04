//
// Created by nrot on 04.11.16.
//

#ifndef DISPLAYMUSIC_APPS_WAVE_FILE_H
#define DISPLAYMUSIC_APPS_WAVE_FILE_H

#endif //DISPLAYMUSIC_APPS_WAVE_FILE_H

//
// Created by nrot on 04.11.16.
//

#include <aquila/source/WaveFile.h>

Aquila::SampleType max_amplitude(Aquila::WaveFile track);

Aquila::SampleType min_amplitude(Aquila::WaveFile track);

unsigned long int max_amplitude_index(Aquila::WaveFile track);

unsigned long int min_amplitude_index(Aquila::WaveFile track);

Aquila::SampleType *medium_apmlitude_array(Aquila::WaveFile track, Aquila::FrequencyType frequency);