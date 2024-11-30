#ifndef INTERVAL_H
#define INTERVAL_H

#include "RayTraceWeekendConstants.h"

class Interval
{
public:
    double min, max;

    Interval() : min(+infinity), max(-infinity) {} // Default interval is empty.
    Interval(double min, double max) : min(min), max(max) {}

    double Size() const
    {
        return max - min;
    }
    double clamp(double x) const
    {
        if (x < min)
            return min;
        if (x > max)
            return max;
        return x;
    }

    bool Contains(double x) const
    {
        return min <= x && x <= max;
    }

    bool Surrounds(double x) const
    {
        return min < x && x < max;
    }

    static const Interval empty, universe;

protected:
private:
};

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe= Interval(-infinity, +infinity);

#endif
