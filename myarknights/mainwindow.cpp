#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QLabel>
#include<QDebug>
#include "episodes.h"
#include "unit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1280,720);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* ev){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/first.png");
    painter.drawPixmap(0,0,1280,720,pix);
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    this->close();
    Episodes* game=new Episodes;
    game->show();
}


