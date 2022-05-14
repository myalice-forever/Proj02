#include "episodes.h"
#include "ui_episodes.h"
#include<QPushButton>
#include<QPixmap>
#include<QPainter>
#include "gamescene.h"

Episodes::Episodes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Episodes)
{
    ui->setupUi(this);
    this->setFixedSize(1280,720);
    //�޸Ĺؿ�ѡ��ť����ʽ
    QPushButton *lev01 =new QPushButton(this);
    lev01->move(385,70);
    lev01->setFixedSize(510,510);
    lev01->setIconSize(QSize(510,510));
    lev01->setStyleSheet("background-color: rgb(0, 0, 0);");
    lev01->setIcon(QIcon(":/logo_reserve6.png"));
    //ͨ����ť���л�ҳ��
    connect(lev01,&QPushButton::clicked,[=](){
        this->close();
        GameScene* gamescene=new GameScene;
        gamescene->show();
    });
}

void Episodes::paintEvent(QPaintEvent* ev){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/episodes.png");
    painter.drawPixmap(0,0,1280,720,pix);
}

Episodes::~Episodes()
{
    delete ui;
}
