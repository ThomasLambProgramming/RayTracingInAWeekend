#ifndef RAYTRACEWEEKENDCONSTANTS_H
#define RAYTRACEWEEKENDCONSTANTS_H

#include <math.h>
#include <iostream>
#include <limits>
#include <memory>

//Std usings
using std::make_shared;
using std::shared_ptr;

//Useful Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Util functions
inline double DegreeToRadian(double degrees) {return degrees * pi / 180.0;}

//Common Header
#include "Color.h"
#include "Ray.h"
#include "Vector3.h"
#include "Interval.h"

#endif
