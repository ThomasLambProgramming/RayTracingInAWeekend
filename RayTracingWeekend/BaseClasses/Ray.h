#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray
{
public:
    Ray() {}
    Ray(const Point3& origin, const Vector3& direction) : originPoint(origin), rayDirection(direction) {}

    const Point3& Origin() const { return originPoint; }
    const Vector3& Direction () const { return rayDirection; }

    Point3 PositionAt(double t) const
    {
        return originPoint + rayDirection * t;
    }

private:
    Point3 originPoint;
    Vector3 rayDirection;
};

#endif