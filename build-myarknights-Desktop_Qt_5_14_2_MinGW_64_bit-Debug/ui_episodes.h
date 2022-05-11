/********************************************************************************
** Form generated from reading UI file 'episodes.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EPISODES_H
#define UI_EPISODES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Episodes
{
public:

    void setupUi(QWidget *Episodes)
    {
        if (Episodes->objectName().isEmpty())
            Episodes->setObjectName(QString::fromUtf8("Episodes"));
        Episodes->resize(400, 300);

        retranslateUi(Episodes);

        QMetaObject::connectSlotsByName(Episodes);
    } // setupUi

    void retranslateUi(QWidget *Episodes)
    {
        Episodes->setWindowTitle(QCoreApplication::translate("Episodes", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Episodes: public Ui_Episodes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EPISODES_H
