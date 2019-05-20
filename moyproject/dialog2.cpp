#include "dialog2.h"
#include "ui_dialog2.h"

dialog2::dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog2)
{
    ui->setupUi(this);
}

dialog2::~dialog2()
{
    delete ui;
}

void dialog2::on_buttonBox_accepted()
{
    m1 = ui->line1m->text().toDouble();
    m2 = ui->line2m->text().toDouble();
    m3 = ui->line3m->text().toDouble();
    x1 = ui->line1x->text().toDouble();
    x2 = ui->line2x->text().toDouble();
    x3 = ui->line3x->text().toDouble();
    y1 = ui->line1y->text().toDouble();
    y2 = ui->line2y->text().toDouble();
    y3 = ui->line3y->text().toDouble();
    Vx1 = ui->line1Vx->text().toDouble();
    Vx2 = ui->line2Vx->text().toDouble();
    Vx3 = ui->line3Vx->text().toDouble();
    Vy1 = ui->line1Vy->text().toDouble();
    Vy2 = ui->line2Vy->text().toDouble();
    Vy3 = ui->line3Vy->text().toDouble();
    this->close();
}
