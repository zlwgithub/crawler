#ifndef CLOUDDATAACQUISITIONUI_SHOWRESULTSUI
#define CLOUDDATAACQUISITIONUI_SHOWRESULTSUI

#pragma once

#include <QtWidgets/QWidget>
#include "UI/Base/UIDialog.h"
#include <QTreeWidget>
#include <QTableWidget>
#include <QScrollArea>
#include <QMessageBox>
#include<db.h>
#include"public.h"
#include"service.h"
#include <QStackedWidget>
#include<QSharedPointer>
#include<vector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeWidgetItem>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <iostream>

int callback(void* data, int argc, char** argv, char** azColName);

//向表格中加入数据
void addDataToTable(QTableWidget* tableWidget, int argc, char** argv);

struct Pqq
{
	QTableWidget* tableWidget = nullptr;
	QScrollArea* scrollArea = nullptr;
};
class CShowResults : public CUIDialog
{
	Q_OBJECT

public:
	CShowResults(QWidget* parent = nullptr, std::string dbpath = "");
	~CShowResults();
	//用于设置整体界面的样式和字体
	void applyStyles();
	int cur = 0;
	std::vector<Pqq*> qsvec;

public slots:
	void onItemClicked(QTreeWidgetItem* item, int column);

private:
	QWidget* mainWindow = nullptr;

	QTreeWidgetItem* rootItem = nullptr;
	QTreeWidgetItem* qqNumberItem = nullptr;
	QTreeWidgetItem* userInfoItem = nullptr;
	QTreeWidgetItem* contactsItem = nullptr;
	QTreeWidgetItem* messagesItem = nullptr;
	QTreeWidgetItem* photosItem = nullptr;
	QTreeWidgetItem* otherItem = nullptr;

	QTreeWidget* treeWidget = nullptr;

	QHBoxLayout* mainLayout = nullptr;
	QVBoxLayout* leftLayout = nullptr;
	QVBoxLayout* rightLayout = nullptr;
	QSharedPointer<QStackedWidget> stackedWidget;
};
#endif  // CLOUDDATAACQUISITIONUI_SHOWRESULTSUI


