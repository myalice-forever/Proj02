/********************************************************************************
** Form generated from reading UI file 'ending.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENDING_H
#define UI_ENDING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_Ending
{
public:

    void setupUi(QDialog *Ending)
    {
        if (Ending->objectName().isEmpty())
            Ending->setObjectName(QString::fromUtf8("Ending"));
        Ending->resize(400, 300);

        retranslateUi(Ending);

        QMetaObject::connectSlotsByName(Ending);
    } // setupUi

    void retranslateUi(QDialog *Ending)
    {
        Ending->setWindowTitle(QCoreApplication::translate("Ending", "Ending", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Ending: public Ui_Ending {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENDING_H
