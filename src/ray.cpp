#include "ray.h"
#include <cmath>
#include <iostream>

inline bool isEqual(double x, double y, double epsilon = 0.00001f) {
    return (std::abs(x - y) < epsilon) ? true : false;
}

template <typename T>
Ray<T>::Ray(Vector3D<T> orig, Vector3D<T> dir) : origin(orig), direction(dir) {
    if (!isEqual(direction.length_sq(), 1)) {
        std::cout
            << "Created ray with unnormalized direction vector. Fixing...";
        direction.normalize();
    }
}

template struct Ray<float>;