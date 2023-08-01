#ifndef CLOUDDATAACQUISITIONUI_TASKCARDUI
#define CLOUDDATAACQUISITIONUI_TASKCARDUI

#pragma once
#include <QWidget>
#include"UI/Base/SubUIDialog.h"
#include <QLabel>
#include <QLineEdit>

class CTaskCardUi : public CSubUIDialog
{
	Q_OBJECT

public:
	CTaskCardUi(QWidget* parent = nullptr);
	~CTaskCardUi();

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

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	void initUi();
};

#endif //CLOUDDATAACQUISITIONUI_TASKCARDUI
