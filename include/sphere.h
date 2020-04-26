#ifndef SPHERE_H
#define SPHERE_H

#include "nlohmann/json.hpp"
#include "ray.h"
#include "vector3d.h"

template <typename T> class Sphere {
  public:
    Sphere(T x, T y, T z, T radius);
    Sphere(Vector3D<T> center, T radius);
    Sphere(const nlohmann::json &);
    bool intersects(const Ray<T> &, Vector3D<T> &);
    void normalAtPoint(Vector3D<T> &, const Vector3D<T> &);
    void print();

  private:
    Vector3D<T> center;
    T radius;
};
#endif