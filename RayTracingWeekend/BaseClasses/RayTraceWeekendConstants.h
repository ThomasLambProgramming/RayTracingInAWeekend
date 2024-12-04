#ifndef RAYTRACEWEEKENDCONSTANTS_H
#define RAYTRACEWEEKENDCONSTANTS_H

#include <math.h>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

//Std usings
using std::make_shared;
using std::shared_ptr;

//Useful Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Util functions
inline double DegreeToRadian(double degrees) {return degrees * pi / 180.0;}

//Returns a random number in [0,1]
inline double RandomDouble() {return std::rand() / (RAND_MAX + 1.0);}
inline double RandomDouble(double min, double max) {return min + (max-min) * RandomDouble();}

//Alternate number generation from RayTracingInAWeekend using random c++ header
//inline double random_double() {
//    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//    static std::mt19937 generator;
//    return distribution(generator);
//}

//Common Header
#include "Color.h"
#include "Ray.h"
#include "Vector3.h"
#include "Interval.h"

#endif
