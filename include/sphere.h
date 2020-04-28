#ifndef SPHERE_H
#define SPHERE_H

#include "nlohmann/json.hpp"
#include "ray.h"
#include "vector3d.h"

template <typename T> class Sphere {
  public:
    Sphere(T x, T y, T z, T radius);
    Sphere(Vector3D<T> center, T radius);
    Sphere(const nlohmann::json &j);
    bool intersects(const Ray<T> &ray, Vector3D<T> &intersectionPoint,
                    T &distance);
    void normalAtPoint(Vector3D<T> &normal, const Vector3D<T> &point) ;
    void print();
    Vector3D<T> getSurfaceProperties(const Vector3D<T> &intersection,
                                     const Ray<T> &ray);

  private:
    Vector3D<T> center;
    T radius;
    Vector3D<float> color;
};
#endif