#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include "unit.h"

class Enemy;class Cell;
class Hero : public Unit
{
public:
    enum attack_direction{North,South,West,East,Circle};
protected:
    int x;
    int y;
    Cell* cell;
    //攻击属性
    int defence_num;
    bool remote;
    attack_direction direction;
    int attack_range;
    bool aoe_able;
    bool fly_able;
    int attack_turn_count;
    //类别属性
    QString pix_path;
    enum type{prayerr,angler,smirkerr,yummerr};
    type _type;
public:
    int cost;
    int rest_defence_num;
public:
    Hero(double hp,double atk,double atk_interval,double speeds,double _generate_interval,int cost,\
         int defence_num,int _x,int _y,GameScene* parent);
    void Update();
    bool set_cell(Cell* _cell);
    //攻击函数
    bool enemy_in_range();
    bool enemy_on_earth_in_range();
    bool is_remote(){return remote;}
    void remote_attack();
    void AOE();
    void single_attack();
    void close_combat();
    void be_attacked(int atk){current_HP-=atk;if(is_dead())Dead();}
    Hero::attack_direction get_direction(){return direction;}
    void set_direction(attack_direction _direction){
        direction=_direction;
    }
    int get_attack_range(){return attack_range;}
    int get_attack_turn(){return attack_turn_count;}
    //鼠标点击事件
    void mousePressEvent(QMouseEvent* ev);
    //死亡函数
    void Dead();
    ~Hero(){;}
};


//Hero的派生类，期中Angle和Prayer是远程攻击
class Prayer:public Hero{
public:
    Prayer(double hp,double atk,double atk_interval,double speeds,double _generate_interval,int cost,\
          int defence_num,int _x,int _y,GameScene* parent);
    ~Prayer(){;}
};

class Angle:public Hero{
public:
    Angle(double hp,double atk,double atk_interval,double speeds,double _generate_interval,int cost,\
          int defence_num,int _x,int _y,GameScene* parent);
    ~Angle(){;}
};

class Smirker:public Hero{
public:
    Smirker(double hp,double atk,double atk_interval,double speeds,double _generate_interval,int cost,\
          int defence_num,int _x,int _y,GameScene* parent);
    ~Smirker(){;}
};

class Yummer:public Hero{
public:
    Yummer(double hp,double atk,double atk_interval,double speeds,double _generate_interval,int cost,\
          int defence_num,int _x,int _y,GameScene* parent);
    ~Yummer(){;}
};

#endif // HERO_H
