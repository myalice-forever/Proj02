#ifndef CELL_H
#define CELL_H

#include <QLabel>
#include "hero.h"

class Enemy;class Hero;class GameScene;

class Cell : public QLabel
{
    Q_OBJECT
public:
    enum cell_type{
        PATH,//公用路径
        FIRST_PATH,SECOND_PATH,THIRD_PATH,FLY,//三条路径，飞行路径
        BLOCKED,//被阻挡
        PLACEABLE,//可放置
        SIDES,//路边
        START,END//起始点和终点
    };
    bool blocked;//BLOCKED代表被阻挡，blocked代表放置了干员
    //存放该格子上的干员和敌人
    QList<Enemy*> enemy_lst;
    Hero* hero_in_cell;
    int column;
    int row;
    int pix_height;
    int pix_width;
private:
    cell_type original_type;
    cell_type type;
    GameScene* parent;
public:
    Cell(int _row,int _col,cell_type _type,GameScene* parent);
    int get_column(){return column;}
    int get_row(){return row;}
    int get_width(){return pix_width;}
    int get_height(){return pix_height;}
    Cell:: cell_type get_type(){return type;}
    Cell:: cell_type get_original_type(){return original_type;}
    void set_type(Cell::cell_type _type){type=_type;}
    //复写鼠标点击事件，实现放置干员
    void mousePressEvent(QMouseEvent *event);
    bool set_hero(Hero* hero);
    void delete_hero()
    {delete hero_in_cell;
        hero_in_cell=nullptr;}
    bool set_enemy(Enemy* enemy);
    //遍历格子中的所有敌人来寻找攻击对象，一个格子只允许放一个干员
    friend Enemy* search_enemy(Cell* cell,Hero* hero);
    friend Hero* search_hero(Cell* cell);
    void delete_enemy(Enemy* enemy);
    //地图的update事件
    void Update();
};

//辅助函数
double get_distance(QLabel* lab1,QLabel* lab2);

#endif // CELL_H
