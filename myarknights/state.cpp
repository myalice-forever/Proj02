#include<QLabel>
#include<QString>
#include "state.h"
#include "ui_state.h"

State::State(int current_HP,int original_HP,int ATK,int cost,QString pix_path,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::State)
{
    ui->setupUi(this);
    this->setFixedSize(300,300);
    QLabel* emoji_label=new QLabel(this);
    emoji_label->setPixmap(QPixmap(pix_path));
    emoji_label->setGeometry(100,50,100,100);
    emoji_label->setScaledContents(true);
    QLabel* label=new QLabel(this);
    label->setText(QString("ORIGINAL HP:%1\nCURRENT HP:%2\nATK:%3\nCOST:%4").arg(original_HP).\
                   arg(current_HP).arg(ATK).arg(cost));
    label->setGeometry(100,150,200,150);
    label->setScaledContents(true);
    emoji_label->show();label->show();
}

State::~State()
{
    delete ui;
}
