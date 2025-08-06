#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// C++ Std Usings
using std::make_shared;
using std::shared_ptr;

// Constants
const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// Utility Functions
inline double degreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}

// Returns a random real in [0,1).
inline double randomDouble() {
    return std::rand() / (RAND_MAX + 1.0);
}

// Returns a random real in [min,max).
inline double randomDouble(double min, double max) {
    return min + (max - min) * randomDouble();
}

inline double linearToGamma(double linearComponent)
{
    if (linearComponent > 0)
        return std::sqrt(linearComponent);
    return 0;
}

// Common Headers
#include "ray.h"
#include "vector3.h"
#include "interval.h"