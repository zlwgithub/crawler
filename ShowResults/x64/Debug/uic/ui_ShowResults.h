/********************************************************************************
** Form generated from reading UI file 'ShowResults.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWRESULTS_H
#define UI_SHOWRESULTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowResultsClass
{
public:

    void setupUi(QWidget *ShowResultsClass)
    {
        if (ShowResultsClass->objectName().isEmpty())
            ShowResultsClass->setObjectName(QString::fromUtf8("ShowResultsClass"));
        ShowResultsClass->resize(600, 400);

        retranslateUi(ShowResultsClass);

        QMetaObject::connectSlotsByName(ShowResultsClass);
    } // setupUi

    void retranslateUi(QWidget *ShowResultsClass)
    {
        ShowResultsClass->setWindowTitle(QCoreApplication::translate("ShowResultsClass", "ShowResults", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowResultsClass: public Ui_ShowResultsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWRESULTS_H
