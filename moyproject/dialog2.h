#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>

namespace Ui {
class dialog2;
}

class dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit dialog2(QWidget *parent = nullptr);
    ~dialog2();
    double m1;
    double m2;
    double m3;
    double x1;
    double x2;
    double x3;
    double y1;
    double y2;
    double y3;
    double Vx1;
    double Vx2;
    double Vx3;
    double Vy1;
    double Vy2;
    double Vy3;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::dialog2 *ui;
};

#endif // DIALOG2_H
