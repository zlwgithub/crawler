#pragma once

#include"UI/Base/UIDialog.h"
#include <QStackedWidget>
#include<QSharedPointer>
#include<vector>
#include "TaskUi.h"

class QStackedWidget;
class QPushButton;
class QVBoxLayout;
class QWidget;
class QHBoxLayout;

class CloudDataAcquisitionUI : public QWidget
{
	Q_OBJECT

public:
	static CloudDataAcquisitionUI& getInstance();
	CloudDataAcquisitionUI(QWidget* parent = nullptr);
	~CloudDataAcquisitionUI();

	void addTask();

private:
	void initUi();

private slots:
	void showTaskList();
	void showTask();
	void createTask();

private:
	QPushButton* pListBtn;
	QPushButton* pAddBtn;

	std::unordered_map<QPushButton*, TaskUi*> ButtontoTaskUiMap;
	QStackedWidget* stackedWidget;

	QHBoxLayout* taskLayout = nullptr;

};

