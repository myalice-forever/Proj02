#ifndef STATE_H
#define STATE_H

#include <QDialog>

namespace Ui {
class State;
}

class State : public QDialog
{
    Q_OBJECT

public:
    explicit State(int current_HP,int original_HP,int ATK,int cost,QString pix_path,QWidget *parent = nullptr);
    ~State();

private:
    Ui::State *ui;
};

#endif // STATE_H
