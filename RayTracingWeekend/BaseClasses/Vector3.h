#ifndef VECTOR3_H
#define VECTOR3_H

#include "RayTraceWeekendConstants.h"

class Vector3
{
public:
    double p[3];
    Vector3() : p{0,0,0} {}
    Vector3(double x, double y, double z) : p{x,y,z} {}
    Vector3(double x) : p{x,x,x} {}

    double x() const { return p[0]; }
    double y() const { return p[1]; }
    double z() const { return p[2]; }

    Vector3 operator-() const { return Vector3(-p[0],-p[1],-p[2]); }
    double operator[](int i ) const { return p[i]; }
    double& operator[](int i) { return p[i]; }

    Vector3& operator*=(double t)
    {
        p[0] *= t;
        p[1] *= t;
        p[2] *= t;
        return *this;
    }
    Vector3& operator+=(const Vector3& vector)
    {
        p[0] += vector.p[0];
        p[1] += vector.p[1];
        p[2] += vector.p[2];
        return *this;
    }
    Vector3& operator /= (const double t)
    {
        return *this *= 1/t;
    }
    
    double SquaredLength() const { return p[0] * p[0] + p[1] * p[1] +  p[2] * p[2]; }
    double Length() const {return std::sqrt(SquaredLength());}

    static Vector3 Random()
    {
        return Vector3(RandomDouble(),RandomDouble(), RandomDouble());
    }
    static Vector3 Random(double min, double max)
    {
        return Vector3(RandomDouble(min,max), RandomDouble(min,max), RandomDouble(min,max));
    }
    bool NearZero() const
    {
        double s = 1e-8;
        return (std::fabs(p[0]) < s && std::fabs(p[1]) < s && std::fabs(p[2]) < s);
    }
};

//Didn't know alias's existed this is useful. (this is used for later to clarify what the data is being used for.)
using Point3 = Vector3;

inline std::ostream& operator << (std::ostream& out, const Vector3& vec)
{
    return out << vec.p[0] << " " << vec.p[1] << " " << vec.p[2];
}
inline Vector3 operator + (const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.p[0] + rhs.p[0], lhs.p[1] + rhs.p[1], lhs.p[2] + rhs.p[2]);
}
inline Vector3 operator - (const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.p[0] - rhs.p[0], lhs.p[1] - rhs.p[1], lhs.p[2] - rhs.p[2]);
}
inline Vector3 operator * (const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.p[0] * rhs.p[0], lhs.p[1] * rhs.p[1], lhs.p[2] * rhs.p[2]);
}

//Cover both lhs * number and number * rhs
inline Vector3 operator * (const double number, const Vector3& rhs)
{
    return Vector3(number * rhs.p[0], number * rhs.p[1], number * rhs.p[2]);
}
inline Vector3 operator * (const Vector3& lhs, const double number)
{
    return Vector3(number * lhs.p[0], number * lhs.p[1], number * lhs.p[2]);
}

inline Vector3 operator / (const Vector3& vector, const double t)
{
    return (1/t) * vector;
}

inline double DotProduct(const Vector3& lhs, const Vector3& rhs)
{
    return  lhs.p[0] * rhs.p[0] +
            lhs.p[1] * rhs.p[1] +
            lhs.p[2] * rhs.p[2];
}
inline Vector3 CrossProduct(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(
        lhs.p[1] * rhs.p[2] - lhs.p[2] * rhs.p[1],
        lhs.p[2] * rhs.p[0] - lhs.p[0] * rhs.p[2],
        lhs.p[0] * rhs.p[1] - lhs.p[1] * rhs.p[0]);
}
inline Vector3 UnitVector(const Vector3& vec)
{
    return vec / vec.Length();
}
inline Vector3 RandomUnitVector()
{
    while (true)
    {
        Vector3 point = Vector3::Random(-1,1);
        double pointLength = point.SquaredLength();
        //if the point is less than one but greater than a very small number (avoid float rounding errors causing a 0/infinity vector)
        if (pointLength <= 1 && pointLength > 1e-160)
            return point / sqrt(pointLength);
    }
}
inline Vector3 RandomOnHemisphere(const Vector3& surfaceNormal)
{
    Vector3 newRandomVector = RandomUnitVector();
    if (DotProduct(newRandomVector, surfaceNormal) > 0.0)
        return newRandomVector;
    else
        return -newRandomVector;
}
inline Vector3 Reflect(const Vector3& vecIn, const Vector3& normal)
{
    return vecIn - 2 * DotProduct(vecIn, normal) * normal;
}

inline Vector3 Refract(const Vector3& uv, const Vector3& n, double EtaiOverEtat)
{
    double cosTheta = std::fmin(DotProduct(-uv,n), 1.0);
    Vector3 rOutPerpendicular = EtaiOverEtat * (uv + cosTheta * n);
    Vector3 rOutParallel = -std::sqrt(std::fabs(1.0 - rOutPerpendicular.SquaredLength())) * n;
    return rOutPerpendicular + rOutParallel;
}

inline Vector3 RandomInsideUnitDisc()
{
    while (true)
    {
        Vector3 p = Vector3(RandomDouble(-1,1), RandomDouble(-1,1), 0);
        if (p.SquaredLength() < 1)
            return p;
    }
}
#endif