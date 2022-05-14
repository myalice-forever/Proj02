#include<QPixmap>
#include<QDebug>
#include<QString>
#include <QTimer>
#include<QList>
#include<QLabel>
#include<QDebug>
#include<QStyle>
#include<QDesktopWidget>
#include<QPainter>
#include<QPaintEvent>
#include<QtGlobal>
#include<QTime>
#include "gamescene.h"
#include "ui_gamescene.h"
#include "config.h"
#include "enemy.h"
#include "hero.h"
#include "unit.h"
#include "cell.h"
#include "ending.h"

//Hero_label class
Hero_label::Hero_label(Hero_type _label_type,GameScene* _parent){
    parent=_parent;
    this->setParent(parent);
    label_type=_label_type;
    switch(_label_type){
    case emoji1:{
        this->setPixmap(QPixmap(":/pleasegod.png"));
        break;
    }
     case emoji2:
        this->setPixmap(QPixmap(":/smileangle.png"));
        break;
    case emoji3:
        this->setPixmap(QPixmap(":/smirk.png"));
        break;
    case emoji4:
        this->setPixmap(QPixmap(":/yummy.png"));
        break;
    case null_type:
        break;
    }
    this->setFixedSize(75,75);
    this->setScaledContents(true);
    this->show();
}
void Hero_label::mousePressEvent(QMouseEvent *event){
    switch(label_type){
    case emoji1:
        parent->hero_type=emoji1;
        break;
    case emoji2:
        parent->hero_type=emoji2;
        break;
    case emoji3:
        parent->hero_type=emoji3;
        break;
    case emoji4:
        parent->hero_type=emoji4;
        break;
    case null_type:
        break;
    }
}

Joker_label::Joker_label(GameScene* parent,int _x,int _y){
    joker_energy=10;
    this->parent=parent;
    x=_x;
    y=_y;
    this->setParent(parent);
    this->setGeometry(x,y,75,75);
    this->setPixmap(QPixmap(":/joker.png"));
    this->setScaledContents(true);
    this->show();
}

void Joker_label::mousePressEvent(QMouseEvent* ev){
    if(ev->button()==Qt::LeftButton){
        parent->resource+=joker_energy;
        qDebug()<<parent->health;
        delete this;
    }
}


GameScene::GameScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameScene)
{
    ui->setupUi(this);
    this->setFixedSize(1280,800);
    this->setGeometry(
            QStyle::alignedRect(
                Qt::LeftToRight,
                Qt::AlignCenter,
                this->size(),
                qApp->desktop()->availableGeometry()
            )
        );
    Init();
}

void GameScene::Init(){
    hero_type=null_type;
    health=10;
    resource=10;
    resource_turn=250;
    round=1;
    original_enemy_num=10;
    current_enemy_num=original_enemy_num;
    enemy_killed=0;
    joker_turn=100;
    joker_turn_count=joker_turn;
    //初始化label，包括resource_label和hero_label
    resource_label=new QLabel(QString("LIFE: %1\nRESOURCE: %2\nROUND: %3").arg(health).arg(resource).arg(round),this);
    resource_label->setGeometry(900,0,200,100);
    resource_label->adjustSize();
    resource_label->show();
    Hero_label* temp1=new Hero_label(emoji1,this);
    hero_label_list.append(temp1);
    Hero_label* temp2=new Hero_label(emoji2,this);
    hero_label_list.append(temp2);
    Hero_label* temp3=new Hero_label(emoji3,this);
    hero_label_list.append(temp3);
    Hero_label* temp4=new Hero_label(emoji4,this);
    hero_label_list.append(temp4);
    for(int i=0;i<4;i++){
        hero_label_list[i]->setGeometry(900,100+75*i,75,75);
    }
    //初始化移动计时器，统一发送信号，移动距离根据移动信息来决定
    move_timer=new QTimer(this);
    resource_timer=new QTimer(this);
    enemy_born_timer=new QTimer(this);
    move_timer->setInterval(25);
    resource_timer->setInterval(25);
    enemy_born_timer->setInterval(1500);
    connect(move_timer,&QTimer::timeout,this,[=](){this->Update();});
    connect(resource_timer,&QTimer::timeout,this,[=](){this->resource_update();});
    connect(enemy_born_timer,&QTimer::timeout,this,[=](){this->enemy_born_update();});
    move_timer->start();resource_timer->start(); enemy_born_timer->start();
    //初始化地图信息，读取配置文件生成相应地图
    map=new Map(this);
    map->load_mapconfig_file(":/level01.txt");

}

void GameScene::Update(){
    //游戏结束条件
//    qDebug()<<health<<"enemy num"<<enemy_num<<"enemy killed"<<enemy_killed;
//    update();
    if(health<=0){
        move_timer->stop();
        enemy_born_timer->stop();
        resource_timer->stop();
        qDebug()<<"You Lose!";
        Ending* end=new Ending(this,this);
        end->show();
    }
    else if(enemy_killed==original_enemy_num){
        qDebug()<<"You win!";
        move_timer->stop();
        enemy_born_timer->stop();
        resource_timer->stop();
        Ending* end=new Ending(this,this);
        end->show();
    }
    //拓展功能，生产小丑
    if(joker_turn_count==0){
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        int row = qrand()%4;
        int col=qrand()%8;
        qDebug()<<row<<col;
        Joker_label* joker_label=new Joker_label(this,col*100,row*100);
        qDebug()<<joker_label->pos();
        joker_turn_count=joker_turn;
    }
    else{
        joker_turn_count--;
    }
    //敌人和我方单位的刷新
    for(int i=0;i<heroes.size();i++){
        Hero* hero=heroes[i];
        if(hero->is_dead()){
            heroes.takeAt(i);
//            delete hero;
            continue;
        }
        hero->Update();
    }
    for(int i=0;i<enemies.size();i++){
        Enemy* enemy=enemies[i];
        if(enemy->is_dead()||enemy->is_reach_end()){
            if(enemy->is_dead())
                enemy->Dead();
            enemies.takeAt(i);
            delete enemy;
            enemy=nullptr;
            qDebug()<<"enemy dead!"<<(enemy==nullptr);
            continue;
        }
        else{enemy->Update();}
    }
}

void GameScene::resource_update(){
    if(resource_turn==0){
        resource+=5;
        resource_turn=250;
    }
    else
        resource_turn--;
//    qDebug()<<resource;
    resource_label->setText(QString("LIFE: %1\nRESOURCE: %2\nROUND: %3").arg(health).arg(resource).arg(round));
}

void GameScene::enemy_born_update(){
    if(current_enemy_num>0){
        Hugger* hugger=new Hugger(800,100,10,10,10,0,map,this);
        enemies.append(hugger);
        current_enemy_num-=1;
        hugger->show();
    }
    return;
}


GameScene::~GameScene()
{
    delete ui;
}
