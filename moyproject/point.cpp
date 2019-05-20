#include "spring.h"
#include "vector.h"
#include "point.h"
#include "widget.h"

Point :: Point() {
    m = 0;
}

Point :: Point(double p, double v, double u, double V1 = 0, double V2 = 0) {
    m = p;
    Vector t(v, u);
    Vector q(V1, V2);
    r = t;
    V = q;
}

double Point :: Weight() {
    return m;
}

void Point :: hook(Spring *spring) {
    if (spring->load(m, r)) {
        s.push_back(spring);
    }
}

void Point :: del_hook() {
    s.pop_back();
}

double Point :: loc_y() {
    return r.y;
}

void Point :: Move(const Vector& dr) {
    r = r + dr;
    for(auto &y : s) {
        y->move(dr);
    }
}

Vector Point :: Movement(double dt) {
    double g = 9.8;
    Vector a = Force(g);
    a = a / m;
    Vector V1 = V;
    V = V + dt * a;
    return dt * V1 + (dt * dt / 2) * a;
}

Vector Point :: Force(double g) {
    Vector f(g * m);
    for(auto &y : s) {
        Vector u = y->force();
        f = f + u;
    }
    return f;
}



void Point::move(){
    Vector v = this->Movement(0.00025);
    this->Move(v);
    s[0]->deform(v.y);
}

