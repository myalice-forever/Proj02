#include<QPropertyAnimation>
#include<QTimer>
#include<QMovie>
#include<QString>
#include<QDebug>
#include "enemy.h"
#include "unit.h"
#include "cell.h"
#include "config.h"
#include "hero.h"
#include "gamescene.h"

Enemy::Enemy(double hp,double atk,double atk_interval,double speeds,double _generate_interval,\
                       int _path_index,Map* _map,GameScene* parent)\
    :Unit(hp,atk,atk_interval,speeds,parent)
{
    //设置路径
    path_index=_path_index;
    pos_index=0;
    this->set_path(_map->paths.at(path_index));
    this->set_cell(path[0]);
    this->setGeometry(cell->x()*80,cell->y()*90,pix_width,pix_height);
    //设置产生间隔
    state=MOVING;
    flying=false;
    remote=false;
    attack_range=100;
    war_addiction=true;
}

void Enemy::init(QString& name){

}

void Enemy::Update(){
    healthbar->setValue((double)(current_HP/original_HP)*100);
    setUpdatesEnabled(false);
    if(is_dead()){
        Dead();
    }
    if(remote){
        this->attack();
    }
    else if(cell->blocked){
        if(flying){
            this->attack();
            if(war_addiction)
                state=ATTACKING;
        }
        else{
//            state=ATTACKING;
            this->attack();
        }
    }
    else{
        state=MOVING;
    }
    if(state==MOVING){
        if(pos_index<path.size()){
            if(this->pos()==QPoint(path[pos_index]->get_row()*100,path[pos_index]->get_column()*100)){
                pos_index++;
                cell->delete_enemy(this);
                if(pos_index==path.size()){
                    current_HP=0;
                    this->reach_end();
                    return;
                }
                cell=path[pos_index];
                cell->set_enemy(this);
        }
//        if(pos_index==path.size()){
//            qDebug()<<"enemy reach end";
//            current_HP=0;
//            this->reach_end();
//            return;
//        }
        int _x=path[pos_index]->get_row()*100-this->pos().x();
        int _y=path[pos_index]->get_column()*100-this->pos().y();
        if(_x==0){
            _y/=abs(path[pos_index]->get_column()*100-this->pos().y());
        }
        else{
            _x/=abs(path[pos_index]->get_row()*100-this->pos().x());
        }
        this->setGeometry(this->pos().x()+_x*2,this->pos().y()+_y*2,pix_width,pix_height);
    }
  }

    setUpdatesEnabled(true);
}

void Enemy::set_path(QList<Cell*> _path){
    path=_path;
}

bool Enemy::set_cell(Cell* _cell){
    Cell::cell_type type=_cell->get_type();
    if(type==Cell::BLOCKED||type==Cell::END||type==Cell::SIDES)
        return false;
    cell=_cell;
    _cell->set_enemy(this);
    return true;
}

void Enemy::be_attacked(int atk){
    current_HP-=atk;
}

void Enemy::attack(){
    if(remote){
        for(int i=0;i<parent->heroes.size();i++){
            auto hero=parent->heroes[i];
            if(get_distance(hero,this)<=attack_range){
//                qDebug()<<"attack hero";
                if(!hero->is_remote())
                    hero->be_attacked(ATK);
            }
        }
    }
    else{
        if(search_hero(cell)){
            qDebug()<<"search hero";
            cell->hero_in_cell->be_attacked(ATK);
        }
    }
//    if(search_hero(cell))
//        cell->hero_in_cell->be_attacked(ATK);
}

void Enemy::Dead(){
    cell->delete_enemy(this);
}

void Enemy::reach_end(){
    cell->delete_enemy(this);
    parent->health--;
    reachend=true;
}

Hugger::Hugger(double hp,double atk,double atk_interval,double speeds,double _generate_interval,\
             int _path_index,Map* map,GameScene* parent):\
             Enemy(hp,atk,atk_interval,_generate_interval,speeds,_path_index,map,parent)
{
    this->setPixmap(QPixmap(":/hug.png"));
    this->setFixedSize(75,75);
    this->setScaledContents(true);
    flying=true;
    this->show();
}

Vomit::Vomit(double hp,double atk,double atk_interval,double speeds,double _generate_interval,\
             int _path_index,Map* map,GameScene* parent):\
             Enemy(hp,atk,atk_interval,_generate_interval,speeds,_path_index,map,parent)
{
    this->setPixmap(QPixmap(":/vomit.png"));
    this->setFixedSize(75,75);
    this->setScaledContents(true);
    remote=true;
    attack_range=200;
    this->show();
}

Wryer::Wryer(double hp,double atk,double atk_interval,double speeds,double _generate_interval,\
             int _path_index,Map* map,GameScene* parent):\
             Enemy(hp,atk,atk_interval,_generate_interval,speeds,_path_index,map,parent)
{
    this->setPixmap(QPixmap(":/wry.png"));
    this->setFixedSize(75,75);
    this->setScaledContents(true);
    this->show();
}

Sweater::Sweater(double hp,double atk,double atk_interval,double speeds,double _generate_interval,\
             int _path_index,Map* map,GameScene* parent):\
             Enemy(hp,atk,atk_interval,_generate_interval,speeds,_path_index,map,parent)
{
    this->setPixmap(QPixmap(":/sweat.png"));
    this->setFixedSize(75,75);
    this->setScaledContents(true);
    flying=true;
    war_addiction=false;
    this->show();
}
