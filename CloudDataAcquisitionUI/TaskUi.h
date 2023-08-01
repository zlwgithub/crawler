#ifndef CLOUDDATAACQUISITIONUI_FIRSTTASKUI
#define CLOUDDATAACQUISITIONUI_FIRSTTASKUI

#pragma once
#include <QWidget>
#include"UI/Base/SubUIDialog.h"
#include <QLabel>
#include <QLineEdit>
#include"service.h"

class TaskUi : public QWidget
{
	Q_OBJECT

public:
	TaskUi(QWidget* parent = nullptr);
	~TaskUi();

private:
	QLabel* firstLayerLabel_1;
	QLabel* firstLayerLabel_2;

	QLabel* secondLayerLabel_1;
	QLabel* secondLayerLabel_2;
	QLabel* secondLayerLabel_3;

private:
	QLineEdit* lineEdit_1;
	QLineEdit* lineEdit_2;
	QLineEdit* lineEdit_3;

private:
	QPushButton* startButton;
	QPushButton* endButton;

private:
	void initUi();
private slots:
	void startTaskBtn();
};

#endif //CLOUDDATAACQUISITIONUI_FIRSTTASKUI
