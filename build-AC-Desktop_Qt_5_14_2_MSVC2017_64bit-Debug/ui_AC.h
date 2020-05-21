/********************************************************************************
** Form generated from reading UI file 'AC.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AC_H
#define UI_AC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ACClass
{
public:

    void setupUi(QWidget *ACClass)
    {
        if (ACClass->objectName().isEmpty())
            ACClass->setObjectName(QString::fromUtf8("ACClass"));
        ACClass->resize(600, 400);

        retranslateUi(ACClass);

        QMetaObject::connectSlotsByName(ACClass);
    } // setupUi

    void retranslateUi(QWidget *ACClass)
    {
        ACClass->setWindowTitle(QCoreApplication::translate("ACClass", "AC", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ACClass: public Ui_ACClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AC_H
