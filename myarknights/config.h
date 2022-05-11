#ifndef CONFIG_H
#define CONFIG_H

#include<vector>
#include<QString>
#include<QPoint>
#include<QByteArray>
#include<QList>
#include<QWidget>

class Cell;class GameScene;
class Map
{
    friend class Enemy;
private:
    int map_x;
    int map_y;
    int paths_count;
    GameScene* parent;
public:
    std::vector<std::vector<Cell*>> maps;
    std::vector<QList<Cell*>> paths;//´¢´æÂ·¾¶
    std::vector<QString> enemy_generator;
public:
    Map(GameScene* parent);
    int get_map_x();
    int get_map_y();
    bool load_mapconfig_file(QString file_path);
    bool upload_mapconfig_file(QString file_path);
};

#endif // CONFIG_H
