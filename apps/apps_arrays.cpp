//
// Created by nrot on 04.11.16.
//

#include <aquila/source/WaveFile.h>

unsigned int len(Aquila::SampleType *array)
{
    unsigned int size = 0;
    while(array[size] != NULL) size++;
    return size;
}