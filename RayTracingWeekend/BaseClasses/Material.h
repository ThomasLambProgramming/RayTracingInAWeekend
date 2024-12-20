﻿#ifndef MATERIAL_H
#define MATERIAL_H

#include "Hittable.h"

class Material
{
public:
    virtual ~Material() = default;
    virtual bool Scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const
    {
        return false;
    }
};

//Flat color without much reflection
class Lambertian : public Material 
{
public:
    Lambertian(const Color& albedo) : albedo(albedo) {}
    bool Scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override
    {
        Vector3 scatterDirection = record.normal + RandomUnitVector();

        //If the vector is very close to 0 we just want to remove it since it can cause nans or other issues.
        if (scatterDirection.NearZero())
            scatterDirection = record.normal;
        
        scatteredRay = Ray(record.point, scatterDirection);
        attenuation = albedo;
        return true;
    }
private:
    Color albedo;
};


class Metal : public Material 
{
public:
    Metal(const Color& albedo, double fuzzAmount) : albedo(albedo), fuzz(fuzzAmount) {}
    bool Scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override
    {
        Vector3 scatterDirection = Reflect(rayIn.Direction(), record.normal);
        if (fuzz > 0.0)
            scatterDirection = UnitVector(scatterDirection) + (fuzz * RandomUnitVector());
        scatteredRay = Ray(record.point, scatterDirection);
        attenuation = albedo;
        return (DotProduct(scatteredRay.Direction(), record.normal) > 0);
    }
private:
    Color albedo;
    double fuzz;
};

//Material like glass / other see through material
class Dielectric : public Material 
{
public:
    Dielectric(double refractionAmount) : refractionIndex(refractionAmount) {}
    bool Scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override
    {
        attenuation = Color(1.0,1.0,1.0);
        double ri = record.isFrontFace ? (1.0/refractionIndex) : refractionIndex;
        Vector3 unitDirection = UnitVector(rayIn.Direction());

        double cosTheta = std::fmin(DotProduct(-unitDirection, record.normal), 1.0);
        double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);
        bool cannotRefract = (ri * sinTheta) > 1.0;
        Vector3 rayOutputDirection;
        if (cannotRefract || Reflectance(cosTheta, ri) > RandomDouble())
            rayOutputDirection = Reflect(unitDirection, record.normal);
        else
            rayOutputDirection = Refract(unitDirection, record.normal, ri);
        
        scatteredRay = Ray(record.point, rayOutputDirection);
        return true;
    }
private:
    double refractionIndex;

    //Glass has different reflectivity depending on the angle we look at it, the math is apparently horrible
    //but this Schlick's approximation is accurate enough to achieve a similar result.
    static double Reflectance(double cosine, double refractionIndex)
    {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - refractionIndex) / (1 + refractionIndex);
        r0 = r0*r0;
        return r0 + (1-r0)*std::pow((1 - cosine),5);
    }
};

#endif
