#ifndef VECTOR3D_H
#define VECTOR3D_H

template <typename T> class Vector3D {
  public:
    Vector3D();
    Vector3D(T scalar_value);
    Vector3D(T x, T y, T z);
    
    T length_sq() const;
    T length() const;
    void normalize();
    void absolute();
    
    T dot(const Vector3D &) const;
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