#ifndef COLOR_H
#define COLOR_H

#include "Vector3.h"
#include "Interval.h"

using Color = Vector3;

inline double LinearToGamma(double linearValue)
{
    if (linearValue > 0)
        return std::sqrt(linearValue);
    return 0;
}

void WriteColor(std::ostream& out, const Color& pixelColor)
{
    double r = pixelColor.x();
    double g = pixelColor.y();
    double b = pixelColor.z();

    r = LinearToGamma(r);
    g = LinearToGamma(g);
    b = LinearToGamma(b);
            
    //Translate the 0,1 component values to the byte range 0,255
    static const Interval colorClamp(0.000, 0.999);
    int rByte = int (256 * colorClamp.clamp(r));
    int gByte = int (256 * colorClamp.clamp(g));
    int bByte = int (256 * colorClamp.clamp(b));

    out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}

#endif