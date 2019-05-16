#include "spring.h"
#include <QTimer>
#include <QDebug>
#include <QTransform>
#include "widget.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <cmath>
#include <math.h>


Spring::Spring(const double& c, const double& x){
    setPixmap(QPixmap(":/images/spring.png"));
    k = c;
    lo = x;
    l = x;
    m1 = 0;
    m2 = 0;
    angle = 0;
    item1 = nullptr;
    item2 = nullptr;
    fixed1 = false;
    fixed2 = false;
    scaley = x/512;
    scalex = 0.25;
    fixator1 = new QGraphicsRectItem(this);
    fixator1->setRect(0,0,10/scalex,10/scaley);
    fixator1->setBrush(Qt::red);
    fixator1->setPos(240,480);
    fixator2 = new QGraphicsRectItem(this);
    fixator2->setRect(0,0,10/scalex,10/scaley);
    fixator2->setBrush(Qt::red);
    fixator2->setPos(240,5 - 30*scaley);
    setTransform(QTransform().scale(scalex,scaley));
    setFlag(QGraphicsItem::ItemIsMovable);
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(col()));
    //connect(timer,SIGNAL(timeout()),this,SLOT(()));
    timer->start(1);
}

double Spring::length() const {
    return l;
}

double Spring::length0() const {
    return lo;
}

double Spring::Stif() const{
    return k;
}

void Spring::deform(const double &dx){
        l += dx;
        scaley += dx/512;
        setTransformationMode(Qt::SmoothTransformation);
        setTransform(QTransform().scale(scalex,scaley));
        fixator1->setRect(0,0,10/scalex,10/scaley);
        fixator2->setRect(0,0,10/scalex,10/scaley);
        fixator2->setPos(240,-5 + 45*scaley);
}

void Spring::fix(const double &i, const double &j){
    x1 = i;
    y1 = j;
    fixed1 = true;
}

bool Spring::load(const double &m){
    if (m1 == 0.0) {
        m1 = m;
        return true;
    }
    else if(m2 == 0.0 && fixed1 == false) {
        m2 = m;
        return true;
    }
    return false;
}

void Spring::move(){
    if(scaley < 0.5){
        deform(10);
    }
}

void Spring::col(){
    if(fixator1->collidingItems().size() !=0 and not fixed1){
        for(QGraphicsItem* j : fixator1->collidingItems()){
            if(j != this){
                fixate(j,1);
                fixed1 = true;
                item1 = j;
            }
        }
    } else if(fixed1){
        fixate(item1,1);
    } if(this->fixator2->collidingItems().size() !=0 and not fixed2){
        for(QGraphicsItem* j : fixator2->collidingItems()){
            if(j != this){
                fixate(j,2);
                fixed2 = true;
                item2 = j;
            }
        }
    } else if(fixed2){
        fixate(item2,2);
    }
}

void Spring::fixate(QGraphicsItem *item, int i){
    if(i == 1){
        item->setPos(this->x()+39,this->y()+(512 - 40)*scaley);
        item->setFlag(QGraphicsItem::ItemIsMovable,false);
    } else if (i == 2){
        item->setPos(this->x()+39,this->y() - 45 + (30*scaley));
        item->setFlag(QGraphicsItem::ItemIsMovable,false);
    }
}


void Spring::rotation(int x){
    //double pi = 3.14;
        angle += x;
        //double a    = pi/180 * angle;
        //double sina = sin(a);
        //double cosa = cos(a);

        /*QTransform rotationTransform(cosa, sina, -sina, cosa, 0, 0);
        QTransform scalingTransform(1, 0, 0, 1, 0, 0);
        QTransform transform = rotationTransform * scalingTransform;
        setTransform(transform);*/
        setTransform(QTransform().rotate(angle).scale(scalex,scaley));
}


void Spring::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if(event->button() == Qt::RightButton){
        rotation(45);
    }
}

