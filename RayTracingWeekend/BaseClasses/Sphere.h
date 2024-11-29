#ifndef SPHERE_H
#define SPHERE_H

#include "RayTraceWeekendConstants.h"
#include "Hittable.h"

class Sphere : public Hittable
{
public:
    Sphere(const Point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}
    
    bool Hit(const Ray& ray, Interval rayT, HitRecord& record) const override
    {
        //I do not fully understand the math behind this but the following is to find how far along a ray (if at all) is the sphere intersecting with it.
        Vector3 oc = center - ray.Origin();
        double a = ray.Direction().SquaredLength();
        double h = DotProduct(ray.Direction(), oc);
        double c = oc.SquaredLength() - (radius * radius);
    
        double discriminant = (h * h) -  (a * c);
        if (discriminant < 0)
            return false;

        
        double sqrtd = std::sqrt(discriminant);
        //Range the nearest root that lies in the acceptable range.
        double root = (h - sqrtd) / a;
        if (!rayT.Surrounds(root))
        {
            root = (h + sqrtd) / a;
            if (!rayT.Surrounds(root))
                return false;
        }

        record.t = root;
        record.point = ray.PositionAt(record.t);
        Vector3 outwardNormal = (record.point - center) / radius;
        record.SetFaceNormal(ray, outwardNormal);
        return true;
    }

private:
    Point3 center;
    double radius;
};
#endif