#include "widget2.h"
#include "ui_widget2.h"
#include "body.h"
#include <QTimer>
#include <QDebug>
#include "dialog2.h"

Widget2::Widget2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget2)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform);
}

Widget2::~Widget2()
{
    delete ui;
}

void Widget2::move(){
    Vector F21, F31, F23, F32, F12, F13;
    F21 = GravForce(*bodies[0], *bodies[1]);
    F31 = GravForce(*bodies[0], *bodies[2]);
    F32 = GravForce(*bodies[1], *bodies[2]);
    Vector nul(0,0);
    F12 = DisVector(nul, F21);
    F13 = DisVector(nul, F31);
    F23 = DisVector(nul, F32);
    Vector R1, R2, R3; // равнодействующие сил
    R1 = AddVector(F21, F31);
    R2 = AddVector(F12, F32);
    R3 = AddVector(F13, F23);
    Movement(R1, *bodies[0]);
    Movement(R2, *bodies[1]);
    Movement(R3, *bodies[2]);
    //qDebug() << bodies[0]->GetCoordinates().x << bodies[0]->GetCoordinates().y;
    //qDebug() << bodies[1]->GetCoordinates().x << bodies[1]->GetCoordinates().y;
    //qDebug() << bodies[2]->GetCoordinates().x << bodies[2]->GetCoordinates().y;
}

void Widget2::on_pushButton_clicked()
{
    scene->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());
    dialog2* dialog = new dialog2();
    dialog->exec();
    Body* body1 = new Body(dialog->x1,dialog->y1,dialog->Vx1,dialog->Vy1,dialog->m1,Qt::red);
    Body* body2 = new Body(dialog->x2,dialog->y2,dialog->Vx2,dialog->Vy2,dialog->m2,Qt::blue);
    Body* body3 = new Body(dialog->x3,dialog->y3,dialog->Vx3,dialog->Vy3,dialog->m3,Qt::green);
    bodies.push_back(body1);
    bodies.push_back(body2);
    bodies.push_back(body3);
    scene->addItem(body1);
    scene->addItem(body2);
    scene->addItem(body3);
    ui->graphicsView->update();
}

void Widget2::on_pushButton_2_clicked()
{
    QTimer* timer = new QTimer();
    if(scene->items().size() != 0)
    {
        connect(timer,SIGNAL(timeout()),this,SLOT(move()));
        timer->start(50);
   }
}
