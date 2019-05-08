#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct Vector {
    double x, y;
    Vector() {
        x = 0;
        y = 0;
    }
    Vector(double u, double v) {
        x = u;
        y = v;
    }
    double Length(){
        return sqrt(x*x + y*y);
    }
}; // структура "вектор"

Vector AddVector(const Vector& v1, const Vector& v2){
    Vector v;
    v.x = v1.x + v2.y;
    v.y = v1.y + v2.y;
    return v;
} // сложение векторов

Vector DisVector(const Vector& v1, const Vector& v2){
    Vector v;
    v.x = v1.x - v2.y;
    v.y = v1.y - v2.y;
    return v;
} // вычитание векторов

class Body{
public:
    void SetCoordinates(int x1, int y1){
        x = x1;
        y = y1;
    }
    Body(double x1, double y1, double v1_1, double v2_1, double m1){
        x = x1;
        y = y1;
        v_x = v1_1;
        v_y = v2_1;
        m = m1;
    }
    double getx() const{
        return x;
    }
    double gety() const{
        return y;
    }
    double getm() const{
        return m;
    }
    double getvx() const{
        return v_x;
    }
    double getvy() const{
        return v_y;
    }

private:
    double x; // координаты
    double y;
    double m;
    double v_x; // скорости
    double v_y;
    string color;
}; // собственно тело

Vector GravForce (Body b1, Body b2){
    Vector r12;
    r12.x = b2.getx() - b1.getx();
    r12.y = b2.gety() - b1.gety();
    Vector F21;
    F21.x = b1.getm() * b2.getm() * r12.x / (r12.Length()*r12.Length()*r12.Length());
    F21.y = b1.getm() * b2.getm() * r12.y / (r12.Length()*r12.Length()*r12.Length());
    return F21;
} // вычисление силы, действующей со 2го тела на 1ое

int main() {
    Body b1(1,1,5,1,1);
    Body b2(2,2,4,-1,0);
    Body b3(4,4,10,-5,0);
    for (int i = 0; i < 1000; i++){
        Vector F21, F31, F23, F32, F12, F13;
        F21 = GravForce(b1, b2);
        F31 = GravForce(b1, b3);
        F32 = GravForce(b2, b3);
        Vector nul(0,0);
        F12 = DisVector(nul, F21);
        F13 = DisVector(nul, F31);
        F23 = DisVector(nul, F32);
        Vector R1, R2, R3; // равнодействующие сил
        R1 = AddVector(F21, F31);
        R2 = AddVector(F12, F32);
        R3 = AddVector(F13, F23);
    }
    return 0;
}