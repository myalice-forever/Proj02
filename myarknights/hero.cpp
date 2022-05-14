#include<QPixmap>
#include<QMovie>
#include <QTimer>
#include<QMouseEvent>
#include<QPixmap>
#include<QPainter>
#include<QPaintEvent>

#include"gamescene.h"
#include "enemy.h"
#include "hero.h"
#include "cell.h"
#include "state.h"
#include "changedirection.h"

Hero::Hero(double hp,double atk,double atk_interval,double speeds,double _generate_interval,int _cost,\
               int _defence_num,int _x,int _y,GameScene* parent):Unit(hp,atk,atk_interval,speeds,parent)
{
    x=_x;
    y=_y;
    cost=_cost;
    defence_num=_defence_num;
    rest_defence_num=defence_num;
    remote=false;
    direction=North;
    attack_range=1;
    attack_turn_count=attack_interval;
    aoe_able=true;
    fly_able=false;
    this->setGeometry(x,y,75,75);
}

void Hero::Update(){
    healthbar->setValue((double)(current_HP/original_HP)*100);
    if(this->is_dead()){
        this->Dead();
    }
    if(fly_able&&enemy_in_range()){
        if(remote)
            remote_attack();
        else
            close_combat();
    }
    else if(enemy_on_earth_in_range()){
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
//                qDebug()<<get_distance(enemy,this);
        if(get_distance(enemy,this)<=attack_range*100&&!enemy->is_flying()){
            return true;
        }
    }
    return false;
}

bool Hero::enemy_in_range(){
    for(int i=0;i<parent->enemies.size();i++){
        auto enemy=parent->enemies[i];
//                qDebug()<<get_distance(enemy,this);
        if(get_distance(enemy,this)<=attack_range*100){
            return true;
        }
    }
    return false;
}

void Hero::remote_attack(){
    if(attack_turn_count==0){
        if(aoe_able){
            AOE();
        }
        else{
            single_attack();
        }
        attack_turn_count=attack_interval;
    }
    else
        attack_turn_count--;
}

void Hero::AOE(){
    int row=cell->get_row();int col=cell->get_column();
    switch(direction){
    case North:{
        for(int i=std::max(0,row-attack_range);i<(int)parent->map->get_map_y()&&i<row;i++){
            for(int j=0;j<(int)parent->map->maps[i][col]->enemy_lst.size();j++){
                auto enemy=parent->map->maps[i][col]->enemy_lst[j];
                if(enemy->is_flying()&&fly_able)
                    enemy->be_attacked(ATK);
                else if(!enemy->is_flying())
                    enemy->be_attacked(ATK);
            }
        }
        break;
    }
    case South:{
        for(int i=std::min(row+1,(int)parent->map->get_map_y());\
            i<(int)parent->map->get_map_y()&&i<row+attack_range;i++){
            for(int j=0;j<(int)parent->map->maps[i][col]->enemy_lst.size();j++){
                auto enemy=parent->map->maps[i][col]->enemy_lst[j];
                if(enemy->is_flying()&&fly_able)
                    enemy->be_attacked(ATK);
                else if(!enemy->is_flying())
                    enemy->be_attacked(ATK);
            }
        }
        break;
    }
    case West:{
        for(int j=std::max(0,col);j<(int)parent->map->get_map_x()&&j<col;j++){
            for(int i=0;i<(int)parent->map->maps[row][j]->enemy_lst.size();i++){
                auto enemy=parent->map->maps[row][j]->enemy_lst[i];
                if(enemy->is_flying()&&fly_able)
                    enemy->be_attacked(ATK);
                else if(!enemy->is_flying())
                    enemy->be_attacked(ATK);
            }
        }
        break;
    }
    case East:{
        for(int j=std::min(col+1,(int)parent->map->get_map_x());\
            j<(int)parent->map->get_map_x()&&j<col+attack_range;j++){
            for(int i=0;i<(int)parent->map->maps[row][j]->enemy_lst.size();i++){
                auto enemy=parent->map->maps[row][j]->enemy_lst[i];
                if(enemy->is_flying()&&fly_able)
                    enemy->be_attacked(ATK);
                else if(!enemy->is_flying())
                    enemy->be_attacked(ATK);
            }
        }
        break;
    }
    case Circle:{
        for(int i=0;i<parent->enemies.size();i++){
            auto enemy=parent->enemies[i];
            if(get_distance(enemy,this)<=attack_range*100){
                if(enemy->is_flying()&&fly_able)
                    enemy->be_attacked(ATK);
                else if(!enemy->is_flying())
                    enemy->be_attacked(ATK);
            }
        }
    }
    }
}

void Hero::single_attack(){
    int row=cell->get_row();int col=cell->get_column();
    //默认朝向为上
    switch(direction){
    case North:{
        for(int i=std::max(0,row-attack_range);i<(int)parent->map->get_map_y()&&i<row;i++){
            Enemy* enemy=search_enemy(parent->map->maps[i][col],this);
            if(!enemy)
                continue;
            else if(enemy->is_flying()&&fly_able)
                enemy->be_attacked(ATK);
            else if(!enemy->is_flying())
                enemy->be_attacked(ATK);
        }
        break;
    }
    case South:{
        for(int i=std::min(row+1,(int)parent->map->get_map_y());\
            i<(int)parent->map->get_map_y()&&i<row+attack_range+1;i++){
            Enemy* enemy=search_enemy(parent->map->maps[i][col],this);
            if(!enemy)
                continue;
            else if(enemy->is_flying()&&fly_able)
                enemy->be_attacked(ATK);
            else if(!enemy->is_flying())
                enemy->be_attacked(ATK);
        }
        break;
    }
    case West:{
        for(int j=std::max(0,col-attack_range);j<(int)parent->map->get_map_x()&&j<col;j++){
            Enemy* enemy=search_enemy(parent->map->maps[row][j],this);
            if(!enemy)
                continue;
            else if(enemy->is_flying()&&fly_able)
                enemy->be_attacked(ATK);
            else if(!enemy->is_flying())
                enemy->be_attacked(ATK);
        }
        break;
    }
    case East:{
        for(int j=std::min(col+1,(int)parent->map->get_map_x());\
            j<(int)parent->map->get_map_x()&&j<col+attack_range+1;j++){
            Enemy* enemy=search_enemy(parent->map->maps[row][j],this);
            if(!enemy){
                continue;
            }
            else if(enemy->is_flying()&&fly_able)
                enemy->be_attacked(ATK);
            else if(!enemy->is_flying())
                enemy->be_attacked(ATK);
        }
        break;
    }
    case Circle:{
        bool enemy_attack=false;
        for(int i=0;i<parent->enemies.size();i++){
            auto enemy=parent->enemies[i];
            if(enemy_attack)
                break;
            if(get_distance(enemy,this)<=attack_range*100){
                if(enemy->is_flying()&&fly_able){
                    enemy->be_attacked(ATK);
                    enemy_attack=true;
                }
                else if(!enemy->is_flying()){
                    enemy->be_attacked(ATK);
                    enemy_attack=true;
                }
            }
        }
    }
    }
}

//只能攻击本格内的敌人
void Hero::close_combat(){
    //    qDebug()<<"hero search enemy";
    if(attack_turn_count==0){
        Enemy* enemy=search_enemy(cell,this);
        if(!enemy)
            return;
        if(enemy->is_flying()){
            if(fly_able)
                enemy->be_attacked(ATK);
        }
        else{
            enemy->be_attacked(ATK);
        }
        attack_turn_count=attack_interval;
    }
    else
        attack_turn_count--;
}

void Hero::mousePressEvent(QMouseEvent* ev){
    int row=cell->get_row();int col=cell->get_column();
    if(ev->button()== Qt::LeftButton){
        QTimer* temp_timer=new QTimer(this);
        if(!remote){
            cell->setPixmap(QPixmap(":/show_direction1.png"));
            temp_timer->singleShot(1000,[=](){
                cell->setPixmap(QPixmap(cell->pix_path));
            });
        }
        else{
            switch(direction){
            case North:{
                for(int i=std::max(0,row-attack_range);i<std::min((int)parent->map->maps.size(),row);i++){
                    auto _cell=parent->map->maps[i][col];
                    _cell->setPixmap(QPixmap(":/show_direction1.png"));
                    _cell->show();
                }
                temp_timer->singleShot(1000,[=](){
                    for(int i=std::max(0,row-attack_range);i<std::min((int)parent->map->maps.size(),row);i++){
                        auto _cell=parent->map->maps[i][col];
                        _cell->setPixmap(QPixmap(_cell->pix_path));
                        _cell->show();
                    }
                });
                break;
            }
            case South:{
                for(int i=row;i<(int)parent->map->maps.size()&&i<row+attack_range;i++){
                    auto _cell=parent->map->maps[i][col];
                    _cell->setPixmap(QPixmap(":/show_direction1.png"));
                    _cell->show();
                }
                temp_timer->singleShot(1000,[=](){
                    for(int i=row;i<std::min((int)parent->map->maps.size(),row+attack_range);\
                        i++){
                        auto _cell=parent->map->maps[i][col];
                        _cell->setPixmap(QPixmap(_cell->pix_path));
                        _cell->show();
                    }
                });
                break;
            }
            case West:{
                for(int j=std::max(0,col-attack_range);j<std::min((int)parent->map->maps[0].size(),col);j++){
                    auto _cell=parent->map->maps[row][j];
                    _cell->setPixmap(QPixmap(":/show_direction1.png"));
                    _cell->show();
                }
                temp_timer->singleShot(1000,[=](){
                    for(int j=std::max(0,col-attack_range);j<std::min((int)parent->map->maps[0].size(),col);j++){
                        auto _cell=parent->map->maps[row][j];
                        _cell->setPixmap(QPixmap(_cell->pix_path));
                        _cell->show();
                    }
                });
                break;
            }
            case East:{
                for(int j=col;j<std::min((int)parent->map->maps[0].size(),col+attack_range);j++){
                    auto _cell=parent->map->maps[row][j];
                    _cell->setPixmap(QPixmap(":/show_direction1.png"));
                    _cell->show();
                }
                temp_timer->singleShot(1000,[=](){
                    for(int j=col;j<std::min((int)parent->map->maps[0].size(),col+attack_range);j++){
                        auto _cell=parent->map->maps[row][j];
                        _cell->setPixmap(QPixmap(_cell->pix_path));
                        _cell->show();
                    }
                });
                break;
            }
            case Circle:{
                int r=attack_range*100;
                QLabel* range_label=new QLabel(parent);
                range_label->setGeometry(pos().x()-r/2,pos().y()-r/2,r,r);
                range_label->setPixmap(QPixmap(":/circle.png"));
                range_label->setScaledContents(true);
                range_label->show();
                qDebug()<<range_label->pos();
                temp_timer->singleShot(1000,[=](){
                    delete range_label;
                });
            }
            }
        }
        delete temp_timer;
    }
    else if(ev->button()==Qt::RightButton){
        QTimer* show_state_timer=new QTimer(this);
        State* state_dialog=new State(current_HP,original_HP,ATK,cost,pix_path,parent);
        state_dialog->show();
        show_state_timer->singleShot(1000,[=](){
            delete state_dialog;
        });
        delete show_state_timer;
    }
    else if(ev->button()==Qt::MidButton){
        QString _direction;
        switch(direction){
        case North:
            _direction="NORTH";
            break;
        case South:
            _direction="SOUTH";
            break;
        case West:
            _direction="WEST";
            break;
        case East:
            _direction="EAST";
            break;
        case Circle:
            _direction="CIRCLE";
            break;
        }
        ChangeDirection* dia=new ChangeDirection(_direction,pix_path,this,parent);
        dia->show();
    }
}



void Hero::Dead(){
    cell->set_type(cell->get_original_type());
    cell->blocked=false;
    cell->delete_hero();
}

//远程攻击角色为Prayer和Angle,其中Angle可攻击飞行单位，aoe。Prayer是单体攻击
//近战角色为Smirker和Yummer,其中Yummer可以攻击飞行单位

Prayer::Prayer(double hp,double atk,double atk_interval,double speeds,double _generate_interval,int cost,\
             int defence_num,int _x,int _y,GameScene* parent):Hero(hp,atk,atk_interval,\
                                                                   speeds,_generate_interval,cost,defence_num,\
                                                                   _x,_y,parent)
{
    pix_path=":/pleasegod.png";
    _type=prayerr;
    this->setPixmap(QPixmap(":/pleasegod.png"));
    this->setFixedSize(75,75);
    this->setScaledContents(true);
    parent->resource-=cost;
    remote=true;
    attack_range=2;
    direction=Circle;
    aoe_able=false;
    this->show();
}

Angle::Angle(double hp,double atk,double atk_interval,double speeds,double _generate_interval,int cost,\
             int defence_num,int _x,int _y,GameScene* parent):Hero(hp,atk,atk_interval,speeds,\
                                                                   _generate_interval,cost,defence_num,\
                                                                   _x,_y,parent)
{
    pix_path=":/smileangle.png";
    _type=angler;
    this->setPixmap(QPixmap(":/smileangle.png"));
    this->setFixedSize(75,75);
    this->setScaledContents(true);
    parent->resource-=cost;
    remote=true;
    attack_range=2;
    aoe_able=true;
    fly_able=true;
    this->show();
}

Smirker::Smirker(double hp,double atk,double atk_interval,double speeds,double _generate_interval,int cost,\
             int defence_num,int _x,int _y,GameScene* parent):Hero(hp,atk,atk_interval,speeds,\
                                                                   _generate_interval,cost,defence_num,\
                                                                   _x,_y,parent)
{
    pix_path=":/smirk.png";
    _type=smirkerr;
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
    pix_path=":/yummy.png";
    _type=yummerr;
    this->setPixmap(QPixmap(":/yummy.png"));
    this->setFixedSize(75,75);
    this->setScaledContents(true);
    parent->resource-=cost;
    remote=true;
    attack_range=2;
    fly_able=true;
    this->show();
}
