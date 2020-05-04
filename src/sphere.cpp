#include "sphere.h"
#include "spdlog/spdlog.h"
#include <cmath>
#include <iostream>

template <typename T>
Sphere<T>::Sphere(T x, T y, T z, T radius) : center(x, y, z), radius(radius) {}

template <typename T>
Sphere<T>::Sphere(Vector3D<T> center, T radius, Vector3D<float> color)
    : center(center), radius(radius), color(color) {}

template <typename T>
Sphere<T>::Sphere(const nlohmann::json &j)
    : center(j["center"]["x"].get<T>(), j["center"]["y"].get<T>(),
             j["center"]["z"].get<T>()),
      radius(j["radius"].get<T>()),
      color(static_cast<std::vector<float>>(j["color"])) {}

template <typename T> void Sphere<T>::print() {
    std::cout << "Instantiated a sphere with color ";
    color.print(' ');
    std::cout << "and radius " << radius << " at center ";
    center.print();
}

template <typename T> void Sphere<T>::log() {
    auto logger = spdlog::get("log");
    logger->info("Instantiated a sphere with color ({}, {}, {}) and radius {} "
                 "at center ({}, {}, {})",
                 color.X(), color.Y(), color.Z(), radius, center.X(),
                 center.Y(), center.Z());
}

template <typename T>
Vector3D<T> Sphere<T>::getSurfaceProperties(const Vector3D<T> &intersection,
                                            const Ray<T> &ray) {
    Vector3D<float> normal;
    this->normalAtPoint(normal, intersection);
    float facingRatio = std::max(normal.dot(ray.direction * -1), 0.0f);
    return color * facingRatio;
}

template <typename T>
void Sphere<T>::normalAtPoint(Vector3D<T> &normal, const Vector3D<T> &point) {
    normal = point - center;
    normal.normalize();
    // return normal;
}

template <typename T>
bool Sphere<T>::intersects(const Ray<T> &ray, Vector3D<T> &intersectionPoint,
                           T &distance) {
    // Computes the intersection of the sphere with a ray (has origin vector and
    // direction). Also yields the intersection point.
    T a = 1;
    Vector3D<T> origin_to_center = ray.origin - center;
    T b = 2 * ray.direction.dot(origin_to_center);
    T c = origin_to_center.length_sq() - radius * radius;

    T discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;
    else {
        // std::cout << "Discriminant is: " << discriminant << "\t";
        // std::cout << "Intersected!\t";
        // Now need to compute the solution to the quadratic equation
        T sol1 = (-1 * b + sqrt(discriminant)) / 2.0;
        T sol2 = (-1 * b - sqrt(discriminant)) / 2.0;
        // std::cout << "Sol1 = " << sol1 << "\tSol2 = " << sol2 << "\t";
        if (sol1 > sol2) {
            if (sol2 > 0)
                std::swap(sol1, sol2);
            if (sol1 < 0) {
                std::cout << "Both intersections are behind the origin"
                          << "\n";
                return false;
            }
        } else {
            if (sol2 > 0)
                std::swap(sol1, sol2);
            else {
                std::cout << "Both intersections are behind the origin"
                          << "\t";
                return false;
            }
        }
        // Now sol1 is the one we want to work with. Changing this to a point
        // involves using the equation (Origin + t*Direction).
        // Sol1 is the distance from the origin, which is also something we need
        // to know to decide which sphere is the closest to the camera.
        intersectionPoint = ray.origin + ray.direction * sol1;
        distance = sol1;
        return true;
    }
}

template class Sphere<float>;