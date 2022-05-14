/********************************************************************************
** Form generated from reading UI file 'state.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATE_H
#define UI_STATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_State
{
public:

    void setupUi(QDialog *State)
    {
        if (State->objectName().isEmpty())
            State->setObjectName(QString::fromUtf8("State"));
        State->resize(400, 300);

        retranslateUi(State);

        QMetaObject::connectSlotsByName(State);
    } // setupUi

    void retranslateUi(QDialog *State)
    {
        State->setWindowTitle(QCoreApplication::translate("State", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class State: public Ui_State {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATE_H
