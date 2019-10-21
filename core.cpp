#include "core.h"

Vector3::Vector3(): x(0), y(0), z(0) {}
Vector3::Vector3(const real x, const real y, const real z) : x(x), y(y), z(z) {} 

//invert
void Vector3::invert() {
    x = -x;
    y = -y;
    z = -z;
}

//clear the vector
void Vector3::clear() {
    x = 0;
    y = 0;
    z = 0;
}

//magnitude
real Vector3::magnitude() const {
    return real_sqrt(x*x + y*y + z*z);
}

//square Magnitude
real Vector3::squareMagnitude() const {
    return x*x + y*y + z*z;
}

//normalie
void Vector3::normalize() {
    double mag = squareMagnitude();
    if(mag > 0)
        (*this) *= 1.0f/mag;
}

//operator *= scalar multipliation
void Vector3::operator*=(const real value) {
    x *= value;
    y *= value;
    z *= value;
}

//operator * return a new vector scaled to the new value
Vector3 Vector3::operator*(const real value) {
    return Vector3(x*value, y*value, z*value);
}

//operator += same vector added value
void Vector3::operator+=(const Vector3 v) {
    x += v.x;
    y += v.y;
    z += v.z;
}


//operator + return a new vector
Vector3 Vector3::operator+(const Vector3 v) {
    return Vector3(x+v.x, y+v.y, z+v.z);
}


//operator -= same vector subtract value
void Vector3::operator-=(const Vector3 v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

//operator - return a new vector
Vector3 Vector3::operator-(const Vector3 v) {
    return Vector3(x-v.x, y-v.y, z-v.z);
}


//add scaled value  a + cb to a
void Vector3::addScaledVector(const Vector3 v, const real r) {
    x += r * v.x;
    y += r * v.y;
    z += r * v.z;
}

//return component product element wise
Vector3 Vector3::componentProduct(const Vector3 v) {
    return Vector3(v.x*x, v.y*y, v.z*z);
}

//update with component product element wise
void Vector3::componentProductUpdate(const Vector3 v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
}

//dot product
real Vector3::scalarProduct(const Vector3 v) {
    return (x * v.x + y * v.y + z * v.z);
}

//overload * for dot product vectors
real Vector3::operator*(const Vector3 v) {
    return (x * v.x + y * v.y + z * v.z);
}

//vector product which is cross product
Vector3 Vector3::vectorProduct(Vector3 vector) {
    return Vector3(y*vector.z-z*vector.y,
            z*vector.x-x*vector.z,
            x*vector.y-y*vector.x);
}


//update the current vector with the product of its current value
void Vector3::operator%=(Vector3 vector) {
    (*this) = vectorProduct(vector);
}

//overload %
Vector3 Vector3::operator%(Vector3 vector) {
    return Vector3(y*vector.z-z*vector.y,
            z*vector.x-x*vector.z,
            x*vector.y-y*vector.x);
}
