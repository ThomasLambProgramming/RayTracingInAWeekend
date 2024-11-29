#ifndef VECTOR3_H
#define VECTOR3_H

#include "RayTraceWeekendConstants.h"

class Vector3
{
public:
    double p[3];
    Vector3() : p{0,0,0} {}
    Vector3(double x, double y, double z) : p{x,y,z} {}

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

#endif