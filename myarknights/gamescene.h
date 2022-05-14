#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QMainWindow>
#include <QLabel>
#include <QQueue>
#include<QPushButton>
#include "config.h"

class Hero;class Enemy;
enum Hero_type{emoji1,emoji2,emoji3,emoji4,null_type};
class Vomit;class Hero;class Enemy;

class resources:public QLabel{
public:
    int resource_amount;
public:

};

class Hero_label:public QLabel{
private:
    Hero_type label_type;
    GameScene* parent;
public:
    Hero_label(Hero_type label_type,GameScene* parent);
    void mousePressEvent(QMouseEvent *event);
};

class Joker_label:public QLabel{
public:
    int joker_energy;
    int x;
    int y;
    GameScene* parent;
public:
    Joker_label(GameScene* parent,int x,int y);
    ~Joker_label(){;}
    void mousePressEvent(QMouseEvent* ev);
};


namespace Ui {
class GameScene;
}

class GameScene : public QMainWindow
{
    Q_OBJECT

public:
    Map* map;
    //游戏界面属性
    int health;
    int round;
    int resource;
    int resource_turn;
    int enemy_killed;
    int joker_turn;
    int joker_turn_count;
    //敌方和我方单位
    QList<Hero*> heroes;
    QList<Enemy*> enemies;
    //当前选择放置的英雄种类
    Hero_type hero_type;
    //绘制攻击区域所需相关属性

private:
    QLabel* resource_label;
    QList<QLabel*> hero_label_list;
    //定时器
public:
    QTimer* move_timer;
    QTimer* resource_timer;
    QTimer* enemy_born_timer;
    //游戏属性
    int original_enemy_num;
    int current_enemy_num;


public:
    explicit GameScene(QWidget *parent = nullptr);
    ~GameScene();
    void Init();
    void Update();
    void resource_update();
    void enemy_born_update();
private:
    Ui::GameScene *ui;

};

#endif // GAMESCENE_H
