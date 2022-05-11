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
protected:
    enum attacker_state{MOVING,ATTACKING,ATTACKED};
    double generate_interval;
    QPoint generate_place;
    //״̬
    Cell* cell;
    bool flying;
    bool war_addiction;
    bool remote;
    int attack_range;
    attacker_state state;
    QList<Cell*> path;
    int path_index;
    int pos_index;
    bool reachend;

public:
    Enemy(double hp,double atk,double atk_interval,double speeds,double _generate_interval,\
             int path_index,Map* _map,GameScene* parent);
    void init(QString& name);
    bool is_flying(){return flying;}
    void Update();
    void set_path(QList<Cell*> _path);
    bool set_cell(Cell* _cell);
    void attack();
    void be_attacked(int atk);
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
