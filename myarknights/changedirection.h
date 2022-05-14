#ifndef CHANGEDIRECTION_H
#define CHANGEDIRECTION_H

#include <QDialog>

class Hero;
namespace Ui {
class ChangeDirection;
}

class ChangeDirection : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeDirection(QString direction,QString pix_path,Hero* hero,QWidget *parent = nullptr);
    ~ChangeDirection();

private:
    Ui::ChangeDirection *ui;
};

#endif // CHANGEDIRECTION_H
