#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <vector>

template <typename T> class Vector3D {
  public:
    Vector3D();
    Vector3D(const T &scalar_value);
    Vector3D(const T &x, const T &y, const T &z);
    Vector3D(const std::vector<T> &vec);

    T length_sq() const;
    T length() const;
    void normalize();
    void absolute();

    T dot(const Vector3D &vec) const;
    Vector3D<T> operator+(const Vector3D<T> &vec) const;
    Vector3D<T> operator-(const Vector3D<T> &vec) const;
    Vector3D<T> operator*(const T &scalar) const;

    void print(char end = '\n') const;

    T X() const;
    T Y() const;
    T Z() const;

  private:
    T _x, _y, _z;
};

#endif