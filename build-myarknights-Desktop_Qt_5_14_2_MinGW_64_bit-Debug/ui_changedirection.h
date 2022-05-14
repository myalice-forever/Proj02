/********************************************************************************
** Form generated from reading UI file 'changedirection.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEDIRECTION_H
#define UI_CHANGEDIRECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_ChangeDirection
{
public:

    void setupUi(QDialog *ChangeDirection)
    {
        if (ChangeDirection->objectName().isEmpty())
            ChangeDirection->setObjectName(QString::fromUtf8("ChangeDirection"));
        ChangeDirection->resize(400, 300);

        retranslateUi(ChangeDirection);

        QMetaObject::connectSlotsByName(ChangeDirection);
    } // setupUi

    void retranslateUi(QDialog *ChangeDirection)
    {
        ChangeDirection->setWindowTitle(QCoreApplication::translate("ChangeDirection", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeDirection: public Ui_ChangeDirection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEDIRECTION_H
