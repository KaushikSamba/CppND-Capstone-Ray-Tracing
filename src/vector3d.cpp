#include "vector3d.h"
#include <cmath>
#include <iostream>

template <typename T> Vector3D<T>::Vector3D() : _x(0), _y(0), _z(0) {}
template <typename T>
Vector3D<T>::Vector3D(const T &val) : _x(val), _y(val), _z(val) {}
template <typename T>
Vector3D<T>::Vector3D(const T &x, const T &y, const T &z)
    : _x(x), _y(y), _z(z) {}
template <typename T>
Vector3D<T>::Vector3D(const std::vector<T> &vec)
    : _x(vec[0]), _y(vec[1]), _z(vec[2]) {}

template <typename T> T Vector3D<T>::length_sq() const {
    return _x * _x + _y * _y + _z * _z;
}

template <typename T> T Vector3D<T>::length() const {
    return sqrt(length_sq());
};

template <typename T> void Vector3D<T>::normalize() {
    T den = length();
    _x = _x / den;
    _y = _y / den;
    _z = _z / den;
}

template <typename T> void Vector3D<T>::absolute() {
    _x = std::abs(_x);
    _y = std::abs(_y);
    _z = std::abs(_z);
}

template <typename T> T Vector3D<T>::dot(const Vector3D &vec) const {
    return _x * vec._x + _y * vec._y + _z * vec._z;
}

template <typename T>
Vector3D<T> Vector3D<T>::operator+(const Vector3D<T> &vec) const {
    return Vector3D(_x + vec._x, _y + vec._y, _z + vec._z);
}

template <typename T>
Vector3D<T> Vector3D<T>::operator-(const Vector3D<T> &vec) const {
    return Vector3D(_x - vec._x, _y - vec._y, _z - vec._z);
}

template <typename T>
Vector3D<T> Vector3D<T>::operator*(const T &scalar) const {
    return Vector3D(_x * scalar, _y * scalar, _z * scalar);
}

template <typename T> void Vector3D<T>::print(char end) const {
    std::cout << "(" << _x << ", " << _y << ", " << _z << ")" << end;
}

template <typename T> T Vector3D<T>::X() const { return _x; }
template <typename T> T Vector3D<T>::Y() const { return _y; }
template <typename T> T Vector3D<T>::Z() const { return _z; }

template class Vector3D<float>;