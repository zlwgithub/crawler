/********************************************************************************
** Form generated from reading UI file 'CloudDataAcquisitionUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOUDDATAACQUISITIONUI_H
#define UI_CLOUDDATAACQUISITIONUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CloudDataAcquisitionUIClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CloudDataAcquisitionUIClass)
    {
        if (CloudDataAcquisitionUIClass->objectName().isEmpty())
            CloudDataAcquisitionUIClass->setObjectName(QString::fromUtf8("CloudDataAcquisitionUIClass"));
        CloudDataAcquisitionUIClass->resize(600, 400);
        menuBar = new QMenuBar(CloudDataAcquisitionUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        CloudDataAcquisitionUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CloudDataAcquisitionUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CloudDataAcquisitionUIClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CloudDataAcquisitionUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        CloudDataAcquisitionUIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CloudDataAcquisitionUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CloudDataAcquisitionUIClass->setStatusBar(statusBar);

        retranslateUi(CloudDataAcquisitionUIClass);

        QMetaObject::connectSlotsByName(CloudDataAcquisitionUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *CloudDataAcquisitionUIClass)
    {
        CloudDataAcquisitionUIClass->setWindowTitle(QCoreApplication::translate("CloudDataAcquisitionUIClass", "CloudDataAcquisitionUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CloudDataAcquisitionUIClass: public Ui_CloudDataAcquisitionUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOUDDATAACQUISITIONUI_H
