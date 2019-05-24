#ifndef DIALOG_H
#define DIALOG_H
#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QDialog>
#include <utility>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QString text1;
    QString text2;
    QString text3;
private slots:
   void on_buttonBox_rejected();

   void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
