#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QMainWindow>
#include <QLabel>
#include <QQueue>
#include<QPushButton>
#include "config.h"

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


namespace Ui {
class GameScene;
}

class GameScene : public QMainWindow
{
    Q_OBJECT

public:
    Map* map;
    int health;
    QList<Hero*> heroes;
    QList<Enemy*> enemies;
    int resource;
    Hero_type hero_type;
private:
    int round;
    QLabel* resource_label;
    QList<QLabel*> hero_label_list;
    QTimer* move_timer;
    QTimer* resource_timer;
    QTimer* enemy_born_timer;
    int enemy_num;
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
