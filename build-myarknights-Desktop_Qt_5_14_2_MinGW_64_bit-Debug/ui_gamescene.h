/********************************************************************************
** Form generated from reading UI file 'gamescene.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESCENE_H
#define UI_GAMESCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameScene
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GameScene)
    {
        if (GameScene->objectName().isEmpty())
            GameScene->setObjectName(QString::fromUtf8("GameScene"));
        GameScene->resize(800, 600);
        centralwidget = new QWidget(GameScene);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        GameScene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GameScene);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        GameScene->setMenuBar(menubar);
        statusbar = new QStatusBar(GameScene);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GameScene->setStatusBar(statusbar);

        retranslateUi(GameScene);

        QMetaObject::connectSlotsByName(GameScene);
    } // setupUi

    void retranslateUi(QMainWindow *GameScene)
    {
        GameScene->setWindowTitle(QCoreApplication::translate("GameScene", "GameScene", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameScene: public Ui_GameScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESCENE_H
