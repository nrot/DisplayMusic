//
// Created by nrot on 26.11.16.
//
#include "coords.h"

#ifndef DISPLAYMUSIC_MATH_VECTOR_H
#define DISPLAYMUSIC_MATH_VECTOR_H


class line {
    protected:
        coords start, stop;
    public:
        coords getStart();
        coords getStop();
        double getLenght();
        line(coords c1, coords c2);
        line(int x1, int y1, int x2, int y2);
};


#endif //DISPLAYMUSIC_MATH_VECTOR_H
