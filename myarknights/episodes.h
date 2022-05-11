#ifndef EPISODES_H
#define EPISODES_H

#include <QWidget>

namespace Ui {
class Episodes;
}

class Episodes : public QWidget
{
    Q_OBJECT

public:
    explicit Episodes(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev);
    ~Episodes();

private:
    Ui::Episodes *ui;
};

#endif // EPISODES_H
