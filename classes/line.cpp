//
// Created by nrot on 26.11.16.
//

#include "line.h"
#include "coords.h"
#include "math.h"

coords line::getStart() {
    return start;
}

coords line::getStop() {
    return stop;
}

double line::getLenght() {
    return sqrt(pow(stop.x - start.x, 2) + pow(stop.y - start.y, 2));
}

line::line(coords c1, coords c2) {
    start = c1;
    stop = c2;
}

line::line(int x1, int y1, int x2, int y2) {
    start.x = x1;
    start.y = y1;
    stop.x = x2;
    stop.y = y2;
}

