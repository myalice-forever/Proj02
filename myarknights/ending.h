#ifndef ENDING_H
#define ENDING_H

#include <QDialog>
#include<QLabel>
class GameScene;
namespace Ui {
class Ending;
}
class Ending;
class Symbol_label:public QLabel{
    GameScene* parent;
    Ending* _parent;
public:
    Symbol_label(GameScene* parent,Ending* _parent);
    ~Symbol_label(){;};
    void mousePressEvent(QMouseEvent *event);
};

class Ending : public QDialog
{
    Q_OBJECT
public:
    QLabel* comment_label;
private:
    GameScene* _parent;
    Symbol_label* symbol;
public:
    explicit Ending(GameScene* _parent,QWidget* parent = nullptr);
    ~Ending();
private:
    Ui::Ending *ui;
};

#endif // ENDING_H
