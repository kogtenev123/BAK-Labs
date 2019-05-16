#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"
#include "widget2.h"


MainWindow::MainWindow(QWidget* parent) :
    QMainWindow (parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Widget* widget = new Widget();
    widget->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    Widget2* widget = new Widget2();
    widget->show();
}
