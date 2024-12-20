﻿#ifndef SPHERE_H
#define SPHERE_H

#include "RayTraceWeekendConstants.h"
#include "Hittable.h"

class Sphere : public Hittable
{
public:
    Sphere(const Point3& center, double radius, shared_ptr<Material> material) : center(center), radius(std::fmax(0, radius)), material(material)
    {
        //TODO: Put sphere material init here.
    }
    
    bool Hit(const Ray& ray, Interval rayT, HitRecord& record) const override
    {
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
        record.material = material;
        record.point = ray.PositionAt(record.t);
        Vector3 outwardNormal = (record.point - center) / radius;
        record.SetFaceNormal(ray, outwardNormal);
        return true;
    }

private:
    Point3 center;
    shared_ptr<Material> material;
    double radius;
};
#endif