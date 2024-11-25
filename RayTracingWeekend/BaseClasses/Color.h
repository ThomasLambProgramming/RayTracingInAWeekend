#ifndef COLOR_H
#define COLOR_H

#include "Vector3.h"
#include <iostream>

using Color = Vector3;

void WriteColor(std::ostream& out, const Color& pixelColor)
{
    double r = pixelColor.x();
    double g = pixelColor.y();
    double b = pixelColor.z();

    //Translate the 0,1 component values to the byte range 0,255
    int rByte = int (255.999 * r);
    int gByte = int (255.999 * g);
    int bByte = int (255.999 * b);

    out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}

#endif