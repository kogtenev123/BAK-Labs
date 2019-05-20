#ifndef LOAD_H
#define LOAD_H

#include <QGraphicsRectItem>

class Load: public QGraphicsRectItem{

public:
    Load(double m);

    double getm();

private:
    double m;
};



#endif // LOAD_H
