#ifndef CORE_H_
#define CORE_H_

#include <cmath>
using namespace std;
//define real number precision
typedef float real;

//define the opengl libraries
#include <GL/glut.h>
#include <GL/freeglut.h>


//define real sqrt
#define real_sqrt sqrtf
#define real_pow powf
#define real_abs fabsf

class Vector3 {
    public:
        real x;
        real y;
        real z;
    private:
        real pad; //more efficicnet in 4 numbers

    public:
        //constr
        Vector3();
        Vector3(const real x, const real y, const real z);
        
        //invert
        void invert();

        //clear the vector
        void clear() ;

        //magnitude
        real magnitude() const ;

        //square Magnitude
        real squareMagnitude() const ;

        //normalie
        void normalize() ;

        //operator *= scalar multipliation
        void operator*=(const real value);

        //operator * return a new vector scaled to the new value
        Vector3 operator*(const real value);

        //operator += same vector added value
        void operator+=(const Vector3 v);

        //operator + return a new vector
        Vector3 operator+(const Vector3 v) ;

        //operator -= same vector subtract value
        void operator-=(const Vector3 v) ;

        //operator - return a new vector
        Vector3 operator-(const Vector3 v) ;

        //add scaled value  a + cb to a
        void addScaledVector(const Vector3 v, const real r) ;

        //return component product element wise
        Vector3 componentProduct(const Vector3 v) ;

        //update with component product element wise
        void componentProductUpdate(const Vector3 v) ;

        //dot product
        real scalarProduct(const Vector3 v) ;

        //overload * for dot product vectors
        real operator*(const Vector3 v) ;
        
        //vector product which is cross product
        Vector3 vectorProduct(Vector3 vector);


        //update the current vector with the product of its current value
        void operator%=(Vector3 vector) ;
        
        //overload %
        Vector3 operator%(Vector3 vector);
};

#endif 

