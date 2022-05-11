#include "config.h"
#include "cell.h"
#include<QFile>
#include<QDebug>
#include<QPoint>
#include<QList>
#include<QByteArray>
#include<QString>
#include<vector>
#include<QMouseEvent>
#include "hero.h"
#include "gamescene.h"

Map::Map(GameScene* _parent)
{
    map_x=0;
    map_y=0;
    paths_count=0;
    maps.clear();paths.clear();enemy_generator.clear();
    parent=_parent;
//    qDebug()<<"MAP"<<parent;
}

int Map::get_map_x(){
    return map_x;
}

int Map::get_map_y(){
    return map_y;
}

bool Map::load_mapconfig_file(QString file_path){
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
        return false;
    }
    //��ȡmap�Ŀ�ͳ�����#���ָ���
    QString str=file.readLine();
    map_y=str.section("#",0,0).toInt();
    map_x=str.section("#",1,1).toInt();
    //maps.resize(map_width);
    //��ȡmap�Ļ�ͼ��Ϣ,'A'�ǽ�����,'M'�Ǽ���,'W'�ǹ���·��,'O'�������ط�,'P'�ǿɷ���Զ�̸�Ա,'F'��һ��·����
    //'S'�ڶ���·��,'T'������·��
    //��ͼ��ʼ�������������꣬ͼƬ������
    QList<Cell*> fir_path,sec_path,thi_path;
    for(int i=0;i<map_y;i++){
        std::vector<Cell*> temp;
        QByteArray line=file.readLine();
        for(int j=0;j<line.size();j++){
            char type=line[j];
            if(type=='\n')
                break;
            Cell* new_cell;
            switch(type){
            case 'P':
                new_cell=new Cell(j,i,Cell::PLACEABLE,parent);
                new_cell->setPixmap(QPixmap(":/bac2.png"));
                break;
            case 'F':
                new_cell=new Cell(j,i,Cell::FIRST_PATH,parent);
                new_cell->setPixmap(QPixmap(":/bac3.png"));
                fir_path.append(new_cell);
                break;
            case 'S':
                new_cell=new Cell(j,i,Cell::SECOND_PATH,parent);
                new_cell->setPixmap(QPixmap(":/bac3.png"));
                sec_path.append(new_cell);
                break;
            case 'T':
                new_cell=new Cell(j,i,Cell::THIRD_PATH,parent);
                new_cell->setPixmap(QPixmap(":/bac3.png"));
                thi_path.append(new_cell);
                break;
            case 'A':
                new_cell=new Cell(j,i,Cell::START,parent);
                new_cell->setPixmap(QPixmap(":/bac1.png"));
                fir_path.append(new_cell);
                sec_path.append(new_cell);
                thi_path.append(new_cell);
                break;
            case 'M':
                new_cell=new Cell(j,i,Cell::END,parent);
                new_cell->setPixmap(QPixmap(":/bac1.png"));
                fir_path.append(new_cell);
                sec_path.append(new_cell);
                thi_path.append(new_cell);
                break;
            case 'O':
                new_cell=new Cell(j,i,Cell::SIDES,parent);
                new_cell->setPixmap(QPixmap(":/bac4.png"));
                break;
            case 'W': ;
                new_cell=new Cell(j,i,Cell::PATH,parent);
                new_cell->setPixmap(QPixmap(":/bac3.png"));
                fir_path.append(new_cell);
                sec_path.append(new_cell);
                thi_path.append(new_cell); 
                break;
            }
            new_cell->setScaledContents(true);
            temp.push_back(new_cell);
            new_cell->show();
            int width=new_cell->get_width();int height=new_cell->get_height();
            new_cell->setGeometry(j*width,i*height,width,height);
        }
        maps.push_back(temp);
    }
    paths.push_back(fir_path);paths.push_back(sec_path);paths.push_back(thi_path);
//    for(int i=0;i<sec_path.size();i++)
//        qDebug()<<sec_path[i]->pos();
    str=file.readLine();
    int count=file.readLine().toInt();
    for(int i=0;i<count;i++){
        str=file.readLine();
        enemy_generator.push_back(str);
    }
    file.close();
    return true;
}
bool Map::upload_mapconfig_file(QString file_path){
    return true;
}




