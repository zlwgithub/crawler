#ifndef CLOUDDATAACQUISITIONUI_CREATETASKUI
#define CLOUDDATAACQUISITIONUI_CREATETASKUI

#pragma once
#include <QWidget>
#include"UI/Base/UIDialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QStackedWidget>
#include<proxy.h>
#include <QString>

class CreateTaskUi : public QWidget
{
	Q_OBJECT

public:
	CreateTaskUi(QWidget* parent = nullptr);
	~CreateTaskUi();

private:
	QLabel* firstLayerLabel_1;
	QLabel* firstLayerLabel_2;
	QLabel* firstLayerLabel_3;

	QLineEdit* lineEdit_1;
	QLineEdit* lineEdit_2;
	QLineEdit* lineEdit_3;

private:
	QPushButton* startButton;

private slots:
	void saveToDB();
	void sendUrl();

private:
	void initUi();
	void addTask();
	void startTask();
	void GET_QRCODE_MSG_ACK_callback(QString image_path);
};

#endif //CLOUDDATAACQUISITIONUI_CREATETASKUI


