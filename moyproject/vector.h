#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <string>
#include <cmath>


struct Vector {
    double x, y;

    Vector(double u = 0, double v = 0);
    double Length();
}; // структура "вектор"

Vector AddVector(const Vector& v1, const Vector& v2);// сложение векторов

Vector DisVector(const Vector& v1, const Vector& v2);// вычитание векторов

Vector ScalProduct(double a, const Vector& v);// умножение на скаляр

#endif // VECTOR_H
