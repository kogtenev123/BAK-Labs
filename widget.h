
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <point.h>
#include <spring.h>
#include <vector>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void mousePressEvent(QMouseEvent* event);

public slots:
    void move();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    vector<Spring*> springs;
    vector<Point*> points;
    //vector<double> drs;
    Ui::Widget *ui;
    QGraphicsScene *scene;
    int amount;
};

#endif // WIDGET_H
