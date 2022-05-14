#ifndef ENEMY_H
#define ENEMY_H
#include "unit.h"
#include <QWidget>
#include<vector>
#include<QPoint>
#include<QList>
#include "cell.h"

class Map;class Hero;
class Enemy : public Unit
{
    Q_OBJECT
public:
    enum attack_direction{North,South,West,East,Circle};
protected:
    enum attacker_state{MOVING,NOTMOVING};
    double generate_interval;
    QPoint generate_place;
    //状态
    Cell* cell;
    bool flying;
    bool war_addiction;
    bool remote;
    bool aoe_able;
    bool remote_able;
    bool buffed;
    int attack_range;
    attack_direction direction;
    attacker_state state;
    int attack_turn_count;
    QLabel* attacked_label;
    //路径
    QList<Cell*> path;
    int path_index;
    int pos_index;
    bool reachend;

public:
    Enemy(double hp,double atk,double atk_interval,double speeds,double _generate_interval,\
             int path_index,Map* _map,GameScene* parent);
    bool is_flying(){return flying;}
    void Update();
    void set_path(QList<Cell*> _path);
    bool set_cell(Cell* _cell);
    //攻击函数
    bool hero_in_range();
    void remote_attack();
    void aoe_attack();
    void single_attack();
    void close_combat();
    void buff_attack();
    void be_attacked(int atk);
    //死亡或到达我方据点
    void Dead();
    void reach_end();
    bool is_reach_end(){return reachend;}
    ~Enemy(){}
};

class Hugger: public Enemy
{
public:
    Hugger(double hp, double atk, double atk_interval, double speed, double _generate_interval,\
          int _path_index,Map* _map,GameScene* parent\
          );
    ~Hugger(){;}
};


class Vomit: public Enemy
{
public:
    Vomit(double hp, double atk, double atk_interval, double speed, double _generate_interval,\
          int _path_index,Map* _map,GameScene* parent\
          );
};

class Wryer: public Enemy
{
public:
   Wryer(double hp, double atk, double atk_interval, double speed, double _generate_interval,\
          int _path_index,Map* _map,GameScene* parent\
          );
   ~Wryer(){;}
};

class Sweater: public Enemy
{
public:
    Sweater(double hp, double atk, double atk_interval, double speed, double _generate_interval,\
          int _path_index,Map* _map,GameScene* parent\
          );
    ~Sweater(){;}
};
#endif // ENEMY_H
