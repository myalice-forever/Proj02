#include<QPainter>
#include<QPixmap>
#include<QMouseEvent>
#include "ending.h"
#include "ui_ending.h"
#include "gamescene.h"

Symbol_label::Symbol_label(GameScene* parent,Ending* _parent){
    this->parent=parent;
    this->_parent=_parent;
    if(parent->health>0){
        this->setPixmap(QPixmap(":/joker.png"));
    }
    else
       this->setPixmap(QPixmap(":/shao.png"));
    this->setScaledContents(true);
    this->setParent(_parent);
    this->show();
}

void Symbol_label::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        this->setPixmap(QPixmap(":/money.png"));
        this->setGeometry(100,50,300,300);
        this->setFixedSize(300,300);
        _parent->comment_label->setText("SUPPORT THIS PITFUL BIRD");
        _parent->comment_label->setGeometry(50,350,400,100);
        _parent->comment_label->setAlignment(Qt::AlignCenter);
    }
}

Ending::Ending(GameScene* _parent,QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Ending)
{
    ui->setupUi(this);
    this->setFixedSize(500,500);
    this->_parent=_parent;
    symbol=new Symbol_label(_parent,this);
    symbol->setGeometry(200,200,100,100);
    comment_label=new QLabel(this);
    comment_label->setGeometry(200,300,100,100);
    if(_parent->health>0)
        comment_label->setText("YOU WIN!");
    else
        comment_label->setText("YOU LOSE!");
    comment_label->show();
}


Ending::~Ending()
{
    delete ui;
}
