#ifndef HITTIBLE_H
#define HITTIBLE_H

#include "RayTraceWeekendConstants.h"

class HitRecord
{
public:
    Point3 point;
    Vector3 normal;
    double t;
    bool isFrontFace = false;

    void SetFaceNormal(const Ray& ray, const Vector3& outwardNormal)
    {
        //Sets the records normal vector based on if it is the front face or not, note outward is assumed to be a unit vector.
        isFrontFace = DotProduct(ray.Direction(), outwardNormal) < 0;
        normal = isFrontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
public:
    virtual ~Hittable() = default;
    virtual bool Hit(const Ray& ray, Interval rayT, HitRecord& record) const = 0;
};
#endif
