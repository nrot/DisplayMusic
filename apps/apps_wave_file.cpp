//
// Created by nrot on 04.11.16.
//

#include <aquila/source/WaveFile.h>

Aquila::SampleType max_amplitude(Aquila::WaveFile track)
{
    Aquila::SampleType max = 0;
    for(unsigned long int i=0; i < track.getSamplesCount(); i++)
    {
        if(track.sample(i) > max) max = track.sample(i);
    }
    return max;
}

Aquila::SampleType min_amplitude(Aquila::WaveFile track)
{
    Aquila::SampleType min = 0;
    for(unsigned long int i=0; i < track.getSamplesCount(); i++)
    {
        if(track.sample(i) < min) min = track.sample(i);
    }
    return min;
}

unsigned long int max_amplitude_index(Aquila::WaveFile track)
{
    Aquila::SampleType max = 0;
    unsigned long int index = 0;
    for(unsigned long int i=0; i < track.getSamplesCount(); i++)
    {
        if(track.sample(i) > max) {
            max = track.sample(i);
            index = i;
        }
    }
    return index;
}

unsigned long int min_amplitude_index(Aquila::WaveFile track)
{
    Aquila::SampleType min = 0;
    unsigned long int index = 0;
    for(unsigned long int i=0; i < track.getSamplesCount(); i++)
    {
        if(track.sample(i) < min) {
            min = track.sample(i);
            index = i;
        }
    }
    return index;
}

Aquila::SampleType *medium_apmlitude_array(Aquila::WaveFile track, Aquila::FrequencyType frequency)
{
    Aquila::SampleType medium_cof = 0;
    double seconds = track.getSamplesCount()/frequency;
    Aquila::SampleType *medium_apml = new Aquila::SampleType[(int)seconds];

    int z = 0, x =0;
    for(size_t i=0; i<track.getSamplesCount(); i++)
    {
        if(z == frequency)
        {
            medium_apml[x] = medium_cof/frequency;
            x++;
            z = 0;
            medium_cof = 0;
        }
        else {
            z++;
            medium_cof += track.sample(i);
        }
    }

    return medium_apml;
}