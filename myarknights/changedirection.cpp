#include<QString>
#include<QLabel>
#include<QPushButton>
#include "changedirection.h"
#include "ui_changedirection.h"
#include"hero.h"

ChangeDirection::ChangeDirection(QString direction,QString pix_path,Hero* hero,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeDirection)
{
    ui->setupUi(this);
    this->setFixedSize(350,300);
    QLabel* emoji_label=new QLabel(this);
    emoji_label->setPixmap(QPixmap(pix_path));
    emoji_label->setGeometry(100,50,100,100);
    emoji_label->setScaledContents(true);
    emoji_label->show();
    QLabel* label=new QLabel(QString("CURRENT DIRECTION:%1").arg(direction),this);
    label->setGeometry(100,150,100,50);
    label->adjustSize();
    QPushButton* north_btn=new QPushButton(this);
    QPushButton* south_btn=new QPushButton(this);
    QPushButton* west_btn=new QPushButton(this);
    QPushButton* east_btn=new QPushButton(this);
    QPushButton* circle_btn=new QPushButton(this);
    north_btn->setText("NORTH");
    south_btn->setText("SOUTH");
    west_btn->setText("WEST");
    east_btn->setText("EAST");
    circle_btn->setText("CIRCLE");
    circle_btn->adjustSize();
    north_btn->setGeometry(50,200,50,50);
    south_btn->setGeometry(100,200,50,50);
    west_btn->setGeometry(150,200,50,50);
    east_btn->setGeometry(200,200,50,50);
    circle_btn->setGeometry(250,200,50,50);
    connect(north_btn,&QPushButton::clicked,this,[=](){
//        qDebug()<<(Hero*)hero<<hero->get_direction();
        hero->set_direction(Hero::North);
        this->~ChangeDirection();
    });
    connect(south_btn,&QPushButton::clicked,this,[=](){
        hero->set_direction(Hero::South);
        this->~ChangeDirection();
    });
    connect(west_btn,&QPushButton::clicked,this,[=](){
        hero->set_direction(Hero::West);
        this->~ChangeDirection();
    });
    connect(east_btn,&QPushButton::clicked,this,[=](){
        hero->set_direction(Hero::East);
        this->~ChangeDirection();
    });
    connect(circle_btn,&QPushButton::clicked,this,[=](){
        hero->set_direction(Hero::Circle);
        this->~ChangeDirection();
    });
}

ChangeDirection::~ChangeDirection()
{
    delete ui;
}
