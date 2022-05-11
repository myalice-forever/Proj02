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
        PATH,//����·��
        FIRST_PATH,SECOND_PATH,THIRD_PATH,FLY,//����·��������·��
        BLOCKED,//���赲
        PLACEABLE,//�ɷ���
        SIDES,//·��
        START,END//��ʼ����յ�
    };
    bool blocked;//BLOCKED�����赲��blocked��������˸�Ա
    //��Ÿø����ϵĸ�Ա�͵���
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
    //��д������¼���ʵ�ַ��ø�Ա
    void mousePressEvent(QMouseEvent *event);
    bool set_hero(Hero* hero);
    void delete_hero()
    {delete hero_in_cell;
        hero_in_cell=nullptr;}
    bool set_enemy(Enemy* enemy);
    //���������е����е�����Ѱ�ҹ�������һ������ֻ�����һ����Ա
    friend Enemy* search_enemy(Cell* cell,Hero* hero);
    friend Hero* search_hero(Cell* cell);
    void delete_enemy(Enemy* enemy);
    //��ͼ��update�¼�
    void Update();
};

//��������
double get_distance(QLabel* lab1,QLabel* lab2);

#endif // CELL_H
