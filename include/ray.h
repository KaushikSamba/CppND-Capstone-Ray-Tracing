#ifndef RAY_H
#define RAY_H

#include "vector3d.h"

template <typename T> struct Ray {
    Ray(Vector3D<T> origin, Vector3D<T> direction);
    Vector3D<T> origin;
    Vector3D<T> direction;
};

#endif