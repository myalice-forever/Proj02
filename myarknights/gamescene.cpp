#include<QPixmap>
#include<QDebug>
#include<QString>
#include <QTimer>
#include<QList>
#include<QLabel>
#include<QDebug>
#include "gamescene.h"
#include "ui_gamescene.h"
#include "config.h"
#include "enemy.h"
#include "hero.h"
#include "unit.h"
#include "cell.h"

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

GameScene::GameScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameScene)
{
    ui->setupUi(this);
    this->setFixedSize(1280,1000);
    enemy_num=10;
    Init();
}

void GameScene::Init(){
    hero_type=null_type;
    health=10;
    resource=22;
    round=1;
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
    move_timer->setInterval(24);
    resource_timer->setInterval(1000);
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
//    qDebug()<<heroes<<enemies;
    if(health<=0){
        move_timer->stop();
        enemy_born_timer->stop();
        resource_timer->stop();
        qDebug()<<"You Lose!";
    }
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
//            enemy->Dead();
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
    resource+=1;
//    qDebug()<<resource;
    resource_label->setText(QString("LIFE: %1\nRESOURCE: %2\nROUND: %3").arg(health).arg(resource).arg(round));
}

void GameScene::enemy_born_update(){
    if(enemy_num>0){
//        Vomit* vomit=new Vomit(1200,50,10,10,10,0,map,this);
        Wryer* wryer=new Wryer(1200,50,10,10,10,0,map,this);
//        Hugger* hugger=new Hugger(800,20,10,10,10,1,map,this);
//        Sweater* sweater=new Sweater(800,20,10,10,10,1,map,this);
        /*enemies.append(vomit);*/enemies.append(wryer);
        /*enemies.append(hugger);*//*enemies.append(sweater);*/
        enemy_num-=2;
    }
    return;
}

GameScene::~GameScene()
{
    delete ui;
}
