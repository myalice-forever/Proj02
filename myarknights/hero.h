#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include "unit.h"

class Enemy;class Cell;
class Hero : public Unit
{
protected:
    int x;
    int y;
    Cell* cell;
    //攻击属性
    int defence_num;
    bool remote;
    int attack_range;//这里是指圆形攻击区域
    bool circle;
    bool fly_able;
    int maxmum_attack_range;
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
    void close_combat();
    void be_attacked(int atk){current_HP-=atk;if(is_dead())Dead();}
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
