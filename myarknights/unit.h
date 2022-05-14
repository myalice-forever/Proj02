#ifndef UNIT_H
#define UNIT_H

#include <QLabel>
#include<QProgressBar>

class Cell;class GameScene;
class Unit : public QLabel
{
    Q_OBJECT
protected:
    GameScene* parent;

    QProgressBar* healthbar;
    double original_HP;
    double current_HP;
    //¹¥»÷ÊôÐÔ
    double ATK;
    double attack_interval;

    //ÒÆ¶¯
    QTimer* move_timer;
    double speed;

    int pix_height;
    int pix_width;

public:
    Unit(double hp,double atk,double atk_interval,double speeds,GameScene* parent);
    bool is_alive();
    bool is_dead();
    virtual void Dead();
    bool is_attacked();
    virtual void Update();
    ~Unit(){}
};

#endif // UNIT_H
