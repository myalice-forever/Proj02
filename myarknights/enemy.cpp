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
    this->setGeometry(cell->x()*100,cell->y()*100,pix_width,pix_height);
    //设置产生间隔
    state=MOVING;
    reachend=false;
    flying=false;//是否飞行
    remote=false;//是否能远程攻击
    remote_able=false;//是否能攻击我方远程攻击单位
    aoe_able=false;//是否是aoe伤害
    buffed=false;
    attack_range=1;//攻击范围
    direction=Circle;
    war_addiction=true;//是否恋战（恋战只能攻击或移动)
    attack_turn_count=attack_interval;
    attacked_label=new QLabel(parent);
    QFont ft;
    ft.setPointSize(12);
    attacked_label->setFont(ft);
    attacked_label->show();
    QTimer* attacked_timer=new QTimer(this);
    attacked_timer->setInterval(200);
    connect(attacked_timer,&QTimer::timeout,[=](){
        attacked_label->hide();
    });
    attacked_timer->start();
}


void Enemy::Update(){
    healthbar->setValue((double)(current_HP/original_HP)*100);
    setUpdatesEnabled(false);
    if(!remote){
//        qDebug()<<cell->get_row()<<cell->get_column()<<cell->blocked;
        if(cell->blocked){
            close_combat();
            if((flying&&war_addiction)||cell->get_type()==Cell::BLOCKED)
                state=NOTMOVING;
        }
        state=MOVING;
    }
    else if(hero_in_range()){
        if((flying&&war_addiction)||(cell->get_type()==Cell::BLOCKED&&!flying)){
            state=NOTMOVING;
        }
        remote_attack();
    }
    else
        state=MOVING;
    //移动操作
    if(state==MOVING){
        if(pos_index<path.size()){
            if(this->pos()==QPoint(path[pos_index]->get_column()*100,path[pos_index]->get_row()*100)){
                pos_index++;
                cell->delete_enemy(this);
                if(pos_index==path.size()){
//                    qDebug()<<this;
                    this->reach_end();
                    return;
                }
                cell=path[pos_index];
                cell->set_enemy(this);
        }
        int _x=path[pos_index]->get_column()*100-this->pos().x();
        int _y=path[pos_index]->get_row()*100-this->pos().y();
        if(_x==0){
            _y/=abs(path[pos_index]->get_row()*100-this->pos().y());
        }
        else{
            _x/=abs(path[pos_index]->get_column()*100-this->pos().x());
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
//    qDebug()<<"be attacked!"<<atk;
    QString str="-";str+=QString::number(atk);
    attacked_label->setText(str);
    attacked_label->setGeometry(pos().x()+30,pos().y()+25,100,50);
    attacked_label->show();
//    qDebug()<<cell->get_row()<<cell->get_column();
}

bool Enemy::hero_in_range(){
    for(int i=0;i<parent->heroes.size();i++){
        auto hero=parent->heroes[i];
        if(get_distance(hero,this)<=attack_range*100){
            if(hero->is_remote()&&remote_able)
                return true;
            else if(!hero->is_remote())
                return true;
        }
    }
    return false;
}

void Enemy::remote_attack(){
    if(attack_turn_count==0){
        if(aoe_able){
            aoe_attack();
        }
        else
            single_attack();
        attack_turn_count=attack_interval;
    }
    else {
        attack_turn_count--;
    }
}

void Enemy::aoe_attack(){
    int row=cell->get_row();int col=cell->get_column();
    QTimer* temp=new QTimer(this);
    switch(direction){
    case North:{
        for(int i=std::max(0,row-attack_range);i<(int)parent->map->get_map_y()&&i<row;i++){
            auto hero=parent->map->maps[i][col]->hero_in_cell;
            if(hero){
                qDebug()<<i<<col;
                if(hero->is_remote()&&remote_able)
                    hero->be_attacked(ATK);
                else if(!hero->is_remote())
                    hero->be_attacked(ATK);
            }
            parent->map->maps[i][col]->setPixmap(QPixmap(":/show_direction2.png"));
        }
        temp->singleShot(100,[=](){
            for(int i=std::max(0,row-attack_range);i<(int)parent->map->get_map_y()&&i<row;i++){
                parent->map->maps[i][col]->setPixmap(QPixmap(parent->map->maps[i][col]->pix_path));
            }
        });
        break;
    }
    case South:{
        for(int i=row;i<(int)parent->map->get_map_y()&&i<row+attack_range;i++){
            auto hero=parent->map->maps[i][col]->hero_in_cell;
            if(hero){
                if(hero->is_remote()&&remote_able)
                    hero->be_attacked(ATK);
                else if(!hero->is_remote())
                    hero->be_attacked(ATK);
            }
             parent->map->maps[i][col]->setPixmap(QPixmap(":/show_direction2.png"));
        }
        temp->singleShot(15*attack_interval,[=](){
            for(int i=row;i<(int)parent->map->get_map_y()&&i<row+attack_range;i++){
                parent->map->maps[i][col]->setPixmap(QPixmap(parent->map->maps[i][col]->pix_path));
            }
        });
        break;
    }
    case West:{
        for(int j=std::max(0,col);j<(int)parent->map->get_map_x()&&j<col;j++){
            auto hero=parent->map->maps[row][j]->hero_in_cell;
            if(hero){
                if(hero->is_remote()&&remote_able)
                    hero->be_attacked(ATK);
                else if(!hero->is_remote())
                    hero->be_attacked(ATK);
            }
             parent->map->maps[row][j]->setPixmap(QPixmap(":/show_direction2.png"));
        }
        temp->singleShot(15*attack_interval,[=](){
            for(int j=std::max(0,col);j<(int)parent->map->get_map_x()&&j<col;j++){
                parent->map->maps[row][j]->setPixmap(QPixmap(parent->map->maps[row][j]->pix_path));
            }
        });
        break;
    }
    case East:{
        qDebug()<<"north attack";
        for(int j=col;j<(int)parent->map->get_map_x()&&j<col+attack_range;j++){
            auto hero=parent->map->maps[row][j]->hero_in_cell;
            if(hero){
                if(hero->is_remote()&&remote_able)
                    hero->be_attacked(ATK);
                else if(!hero->is_remote()){
                    hero->be_attacked(ATK);}
            }
           parent->map->maps[row][j]->setPixmap(QPixmap(":/show_direction2.png"));
        }
        temp->singleShot(15*attack_interval,[=](){
            for(int j=col;j<(int)parent->map->get_map_x()&&j<col+attack_range;j++){
                parent->map->maps[row][j]->setPixmap(QPixmap(parent->map->maps[row][j]->pix_path));
            }
        });
        break;
    }
    case Circle:{
        for(int i=0;i<parent->enemies.size();i++){
            auto hero=parent->heroes[i];
            if(get_distance(hero,this)<=attack_range*100){
                if(hero->is_remote()&&remote_able)
                    hero->be_attacked(ATK);
                else if(!hero->is_remote())
                    hero->be_attacked(ATK);
            }
        }
    }
    }
    delete temp;
}

void Enemy::single_attack(){
    int row=cell->get_row();int col=cell->get_column();
    switch(direction){
    case North:{
        for(int i=std::max(0,row-attack_range);i<(int)parent->map->get_map_y()&&i<row;i++){
            auto hero=parent->map->maps[i][col]->hero_in_cell;
            if(hero){
                if(hero->is_remote()&&remote_able)
                    hero->be_attacked(ATK);
                else if(!hero->is_remote())
                    hero->be_attacked(ATK);
                break;
            }
        }
        break;
    }
    case South:{
        for(int i=row;i<(int)parent->map->get_map_y()&&i<row+attack_range;i++){
            auto hero=parent->map->maps[i][col]->hero_in_cell;
            if(hero){
                if(hero->is_remote()&&remote_able)
                    hero->be_attacked(ATK);
                else if(!hero->is_remote())
                    hero->be_attacked(ATK);
                break;
            }
        }
        break;
    }
    case West:{
        for(int j=std::max(0,col);j<(int)parent->map->get_map_x()&&j<col;j++){
            auto hero=parent->map->maps[row][j]->hero_in_cell;
            if(hero){
                if(hero->is_remote()&&remote_able)
                    hero->be_attacked(ATK);
                else if(!hero->is_remote())
                    hero->be_attacked(ATK);
                break;
            }

        }
        break;
    }
    case East:{
        for(int j=col;j<(int)parent->map->get_map_x()&&j<col+attack_range;j++){
            auto hero=parent->map->maps[row][j]->hero_in_cell;
            if(hero){
                if(hero->is_remote()&&remote_able)
                    hero->be_attacked(ATK);
                else if(!hero->is_remote())
                    hero->be_attacked(ATK);
                break;
            }
        }
        break;
    }
    case Circle:{
        for(int i=0;i<parent->enemies.size();i++){
            auto hero=parent->heroes[i];
            if(get_distance(hero,this)<=attack_range*100){
                if(hero){
                    if(hero->is_remote()&&remote_able)
                        hero->be_attacked(ATK);
                    else if(!hero->is_remote())
                        hero->be_attacked(ATK);
                    break;
                }
            }
        }
    }
    }
}

void Enemy::close_combat(){
    if(attack_turn_count==0){
        if(cell->blocked){
            cell->hero_in_cell->be_attacked(ATK);
        }
        attack_turn_count=attack_interval;
    }
    else
        attack_turn_count--;
}

void Enemy::buff_attack(){

}

void Enemy::Dead(){
    cell->delete_enemy(this);//将敌人从所在格子中移除
    delete attacked_label;
    parent->enemy_killed++;
}

//敌人到达终点后生命值--
void Enemy::reach_end(){
    cell->delete_enemy(this);
//    qDebug()<<"reach end,health--";
    parent->health-=1;
    parent->enemy_killed++;
    reachend=true;
}

//飞行角色为Hugger和Sweater,其中Sweater为畏战。默认都为恋战
//地面角色中，远程攻击为Vomit,暂时为范围攻击，攻击区域为圆形。近战为Wryer
//近战角色为Hugger
Hugger::Hugger(double hp,double atk,double atk_interval,double speeds,double _generate_interval,\
             int _path_index,Map* map,GameScene* parent):\
             Enemy(hp,atk,atk_interval,_generate_interval,speeds,_path_index,map,parent)
{
    this->setPixmap(QPixmap(":/hug.png"));
    this->setFixedSize(75,75);
    this->setScaledContents(true);
    aoe_able=true;
    remote=true;
    direction=East;
    attack_range=2;
//    flying=true;
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
    aoe_able=true;
    attack_range=2;
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
