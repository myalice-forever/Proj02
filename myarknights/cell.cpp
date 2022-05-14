#include<QMouseEvent>
#include<QDebug>
#include<algorithm>
#include<qmath.h>

#include "cell.h"
#include "hero.h"
#include "enemy.h"
#include "gamescene.h"

int prayer_cost=10;
int angle_cost=20;
int smirker_cost=5;
int yummer_cost=5;

Cell::Cell(int _col,int _row,cell_type _type,GameScene* _parent)
{
    row=_row;
    column=_col;
//    qDebug()<<row<<column;
    pix_height=100;
    pix_width=100;
    type=original_type=_type;
    parent=_parent;
    hero_in_cell=nullptr;
    this->setParent(parent);
    this->setMaximumSize(100,100);
    this->show();
    blocked=false;
}

bool Cell::set_hero(Hero* hero){
    if(!hero)
        return false;
    hero_in_cell=hero;
    blocked=true;
    if(hero->rest_defence_num>0)
        type=BLOCKED;
    return true;
}

bool Cell::set_enemy(Enemy* enemy){
    if(!enemy)
        return false;
    enemy_lst.append(enemy);
    return true;
}

void Cell::delete_enemy(Enemy* enemy){
    for(int i=0;i<enemy_lst.size();i++){
        if(&(*enemy)==&(*enemy_lst[i]))
            enemy_lst.removeAt(i);
    }
}

void Cell::mousePressEvent(QMouseEvent *event)
{
    if(type==PLACEABLE){
        if(event->button()== Qt::LeftButton){
            switch(parent->hero_type){
            case emoji1:{
                if(parent->resource<prayer_cost)
                    return;
                Prayer* prayer=new Prayer(1000,100,0,0,0,prayer_cost,0,this->pos().x(),this->pos().y(),parent);
                parent->heroes.append(prayer);
                prayer->set_cell(this);
                this->set_hero(prayer);
                break;
            }
            case emoji2:{
                if(parent->resource<angle_cost)
                    return;
                Angle* angle=new Angle(150,50,0,0,0,angle_cost,0,this->pos().x(),this->pos().y(),parent);
                parent->heroes.append(angle);
                angle->set_cell(this);
                this->set_hero(angle);
                break;
            }
            default:;
            }
        }
    }
    else if(type==Cell::FIRST_PATH||type==Cell::SECOND_PATH||type==Cell::THIRD_PATH||type==Cell::PATH){
        if(event->button()== Qt::LeftButton)
        {
            switch(parent->hero_type){
            case emoji3:{
                if(parent->resource<smirker_cost)
                    return;
                Smirker* smirker=new Smirker(1000,0,5,0,0,smirker_cost,0,this->pos().x(),this->pos().y(),parent);
                parent->heroes.append(smirker);
                smirker->set_cell(this);
                this->set_hero(smirker);
                break;
            }
            case emoji4:{
                if(parent->resource<yummer_cost)
                    return;
                Yummer* yummer=new Yummer(1000,40,0,0,0,yummer_cost,0,this->pos().x(),this->pos().y(),parent);
                parent->heroes.append(yummer);
                yummer->set_cell(this);
                this->set_hero(yummer);
                break;
            }
            default:;
            }
            parent->hero_type=null_type;
        }
    }
}

//void Cell::Update(){
//     if(!hero_in_cell||hero_in_cell->rest_defence_num>0)
//         type=BLOCKED;
//     type=original_type;
//}

double get_distance(QLabel* lab1, QLabel* lab2){
    int _x=(lab1->pos().x()-lab2->pos().x())*(lab1->pos().x()-lab2->pos().x());
    int _y=(lab1->pos().y()-lab2->pos().y())*(lab1->pos().y()-lab2->pos().y());
    return sqrt(_x+_y);
}

Enemy* search_enemy(Cell* cell,Hero* hero){
    if(cell->enemy_lst.empty()){
        return nullptr;
    }
    Enemy* enemy_min_distance=cell->enemy_lst[0];
    for(int i=0;i<cell->enemy_lst.size();i++){
        Enemy* _enemy=cell->enemy_lst[i];
        if(get_distance(hero,_enemy)<get_distance(hero,enemy_min_distance))
            enemy_min_distance=_enemy;
    }
    return enemy_min_distance;
}


Hero* search_hero(Cell* cell){
    return cell->hero_in_cell;
}


