#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <iostream>

inline bool isEqual(double x, double y, double epsilon = 0.00001f) {
    return (std::abs(x - y) < epsilon) ? true : false;
}

template <typename T> class Vector3D {
  public:
    Vector3D() : _x(0), _y(0), _z(0) {}
    Vector3D(T val) : _x(val), _y(val), _z(val) {}
    Vector3D(T x, T y, T z) : _x(x), _y(y), _z(z) {}
    T length_sq() const { return _x * _x + _y * _y + _z * _z; }
    T length() const { return sqrt(length_sq()); };
    void normalize() {
        T den = length();
        _x = _x / den;
        _y = _y / den;
        _z = _z / den;
    }
    void absolute() {
        _x = std::abs(_x);
        _y = std::abs(_y);
        _z = std::abs(_z);
    }
    T dot(const Vector3D &vec) const {
        return _x * vec._x + _y * vec._y + _z * vec._z;
    }
    Vector3D<T> operator+(const Vector3D<T> &vec) const {
        return Vector3D(_x + vec._x, _y + vec._y, _z + vec._z);
    }
    Vector3D<T> operator-(const Vector3D<T> &vec) const {
        return Vector3D(_x - vec._x, _y - vec._y, _z - vec._z);
    }
    Vector3D<T> operator*(const T &scalar) const {
        return Vector3D(_x * scalar, _y * scalar, _z * scalar);
    }
    void print(char end = '\n') {
        std::cout << "(" << _x << ", " << _y << ", " << _z << ")" << end;
    }
    T X() const { return _x; }
    T Y() const { return _y; }
    T Z() const { return _z; }

  private:
    T _x, _y, _z;
};

template <typename T> T dot(Vector3D<T> &vec1, Vector3D<T> &vec2) {
    return (vec1.X() * vec2.X() + vec1.Y() * vec2.Y() + vec1.Z() * vec2.Z());
}

template <typename T> struct Ray {
    Ray(Vector3D<T> orig, Vector3D<T> dir) : origin(orig), direction(dir) {
        if (!isEqual(direction.length_sq(), 1)) {
            std::cout
                << "Created ray with unnormalized direction vector. Fixing...";
            direction.normalize();
        }
    }
    Vector3D<T> origin;
    Vector3D<T> direction;
};

template <typename T> class Sphere {
  public:
    Sphere(T x, T y, T z, T radius) : center(x, y, z), radius(radius) {}
    Sphere(Vector3D<T> center, T radius) : center(center), radius(radius) {}
    bool intersects(const Ray<T> &, Vector3D<T> &);
    void normalAtPoint(Vector3D<T> &, const Vector3D<T> &);
    void print() {
        std::cout << "Instantiated a sphere of radius " << radius
                  << " at center ";
        center.print();
    }

  private:
    Vector3D<T> center;
    T radius;
};

template <typename T>
void Sphere<T>::normalAtPoint(Vector3D<T> &normal, const Vector3D<T> &point) {
    normal = point - center;
    normal.normalize();
    // return normal;
}

template <typename T>
bool Sphere<T>::intersects(const Ray<T> &ray, Vector3D<T> &intersectionPoint) {
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
        intersectionPoint = ray.origin + ray.direction * sol1;
        return true;
    }
}

#endif