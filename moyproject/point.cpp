#include "spring.h"
#include "vector.h"
#include "point.h"
#include "widget.h"
#include "load.h"
#include <QGraphicsSceneMouseEvent>

Point :: Point() {
    m = 0;
    angle = 0;
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(col()));
    timer->start(1);
}


Point :: Point(double p, double v, double u, double V1 = 0, double V2 = 0) {
    m = p;
    Vector t(v, u);
    Vector q(V1, V2);
    r = t;
    V = q;
    angle = 0;
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(col()));
    timer->start(0);
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
    if (s.size() == 0)
        this->setPos(r.x, r.y);
}

Vector Point :: Movement(double dt) {
    double g = 9.8;
    Vector a = Force(g);
    a = a / m;
    Vector V1 = V;
    V =  V + dt * a;
    V = (1 - m / 1500) * V;
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


void Point::rotation(double a){
        double sina = sin(a);
        double cosa = cos(a);
        QTransform transform(cosa, sina, -sina, cosa, 0, 0);
        setTransform(transform);
}

void Point::col() {
    for(auto& i: springs) {
        if(i->coll()) {
            this->hook(i);
        }
    }   
}

void Point::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if(event->button() == Qt::RightButton){
        angle = 1.57;
        rotation(1.57);
    }
}



