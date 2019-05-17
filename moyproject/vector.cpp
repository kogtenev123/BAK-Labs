#include <vector.h>

Vector::Vector(double u, double v){
    x = u;
    y = v;
}

double Vector::Length(){
    return sqrt(x*x + y*y);
}


Vector AddVector(const Vector& v1, const Vector& v2){
    Vector v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    return v;
}

Vector DisVector(const Vector& v1, const Vector& v2){
    Vector v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    return v;
}

Vector ScalProduct(double a, const Vector& v){
    Vector v1;
    v1.x = a*v.x;
    v1.y = a*v.y;
    return v1;
}
