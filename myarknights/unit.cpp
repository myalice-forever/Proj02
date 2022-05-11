#include "unit.h"
#include "cell.h"
#include "gamescene.h"

#include<QProgressBar>
#include<QMovie>

Unit::Unit(double hp,double atk,double atk_interval,double speeds,GameScene* _parent)
{
    this->setParent(_parent);
    parent=_parent;
    original_HP=hp;
    current_HP=hp;
    ATK=atk;
    attack_interval=atk_interval;
    speed=speeds;
    pix_width=90;
    pix_height=120;
    //ÉúÃüÌõ
    healthbar=new QProgressBar(this);
    healthbar->setMinimum(0);
    healthbar->setMaximum(100);
    healthbar->setValue(current_HP/original_HP*100);
//    qDebug()<<original_HP;
    healthbar->setTextVisible(false);
//    healthbar->setStyleSheet()
    this->show();
}

bool Unit::is_alive(){
    return current_HP>0;
}
bool Unit::is_dead(){
    return !is_alive();
}
void Unit::Dead(){
    this->hide();
}

void Unit::Update(){;}



