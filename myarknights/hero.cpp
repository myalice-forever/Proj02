#include<QPixmap>
#include<QMovie>
#include <QTimer>

#include"gamescene.h"
#include "enemy.h"
#include "hero.h"
#include "cell.h"

Hero::Hero(double hp,double atk,double atk_interval,double speeds,double _generate_interval,int _cost,\
               int _defence_num,int _x,int _y,GameScene* parent):Unit(hp,atk,atk_interval,speeds,parent)
{
    x=_x;
    y=_y;
    cost=_cost;
    defence_num=_defence_num;
    rest_defence_num=defence_num;
    remote=false;
    attack_range=100;
    maxmum_attack_range=200;
    circle=true;
    fly_able=false;
    this->setGeometry(x,y,75,75);
}

void Hero::Update(){
    healthbar->setValue((double)(current_HP/original_HP)*100);
    if(this->is_dead()){
        this->Dead();
    }
    if(enemy_in_range()){
        if(remote)
            remote_attack();
        else
            close_combat();
    }
}

bool Hero::set_cell(Cell* _cell){
    Cell::cell_type type=_cell->get_type();
    if(type==Cell::BLOCKED||type==Cell::END||type==Cell::SIDES)
        return false;
    cell=_cell;
    return true;
}

//
bool Hero::enemy_on_earth_in_range(){
    for(int i=0;i<parent->enemies.size();i++){
        auto enemy=parent->enemies[i];
//        qDebug()<<get_distance(enemy,this);
        if(get_distance(enemy,this)<=attack_range&&!enemy->is_flying()){
            qDebug()<<"enemy in range";
            return true;
        }
    }
    return false;
}

bool Hero::enemy_in_range(){
    for(int i=0;i<parent->enemies.size();i++){
        auto enemy=parent->enemies[i];
//        qDebug()<<get_distance(enemy,this);
        if(get_distance(enemy,this)<=attack_range){
//            qDebug()<<"enemy in range";
            return true;
        }
    }
    return false;
}

void Hero::remote_attack(){
    if(circle){
        if(fly_able){
            for(int i=0;i<parent->enemies.size();i++){
                auto enemy=parent->enemies[i];
                if(get_distance(enemy,this)<=attack_range){
//                    qDebug()<<get_distance(enemy,this);
//                    qDebug()<<"attack";
                    if(fly_able)
                        enemy->be_attacked(ATK);
                }
            }
        }
        else{
            for(int i=0;i<parent->enemies.size();i++){
                auto enemy=parent->enemies[i];
                if(get_distance(enemy,this)<=attack_range&&!enemy->is_flying()){
//                    qDebug()<<get_distance(enemy,this);
//                    qDebug()<<"attack";
                    if(fly_able)
                        enemy->be_attacked(ATK);
                }
            }
        }
    }
    else{
        Enemy* enemy=search_enemy(cell,this);
        if(!enemy)
            return;
        enemy->be_attacked(ATK);
    }
}

void Hero::close_combat(){
    qDebug()<<"hero search enemy";
    Enemy* enemy=search_enemy(cell,this);
    if(!enemy)
        return;
    enemy->be_attacked(ATK);
}

void Hero::Dead(){
//    this->hide();
    cell->set_type(cell->get_original_type());
    cell->blocked=false;
    cell->delete_hero();
}

Prayer::Prayer(double hp,double atk,double atk_interval,double speeds,double _generate_interval,int cost,\
             int defence_num,int _x,int _y,GameScene* parent):Hero(hp,atk,atk_interval,\
                                                                   speeds,_generate_interval,cost,defence_num,\
                                                                   _x,_y,parent)
{
    this->setPixmap(QPixmap(":/pleasegod.png"));
    this->setFixedSize(75,75);
    this->setScaledContents(true);
    parent->resource-=cost;
    remote=true;
    attack_range=200;
    circle=true;
    this->show();
}

Angle::Angle(double hp,double atk,double atk_interval,double speeds,double _generate_interval,int cost,\
             int defence_num,int _x,int _y,GameScene* parent):Hero(hp,atk,atk_interval,speeds,\
                                                                   _generate_interval,cost,defence_num,\
                                                                   _x,_y,parent)
{
    this->setPixmap(QPixmap(":/smileangle.png"));
    this->setFixedSize(75,75);
    this->setScaledContents(true);
    parent->resource-=cost;
    remote=true;
    attack_range=200;
    circle=true;
    fly_able=true;
    this->show();
}

Smirker::Smirker(double hp,double atk,double atk_interval,double speeds,double _generate_interval,int cost,\
             int defence_num,int _x,int _y,GameScene* parent):Hero(hp,atk,atk_interval,speeds,\
                                                                   _generate_interval,cost,defence_num,\
                                                                   _x,_y,parent)
{
    this->setPixmap(QPixmap(":/smirk.png"));
    this->setFixedSize(75,75);
    this->setScaledContents(true);
    parent->resource-=cost;
    this->show();
}

Yummer::Yummer(double hp,double atk,double atk_interval,double speeds,double _generate_interval,int cost,\
             int defence_num,int _x,int _y,GameScene* parent):Hero(hp,atk,atk_interval,speeds,\
                                                                   _generate_interval,cost,defence_num,\
                                                                   _x,_y,parent)
{
    this->setPixmap(QPixmap(":/yummy.png"));
    this->setFixedSize(75,75);
    this->setScaledContents(true);
    parent->resource-=cost;
    fly_able=true;
    this->show();
}
