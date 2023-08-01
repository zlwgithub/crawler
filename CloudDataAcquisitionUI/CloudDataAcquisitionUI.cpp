#include "CloudDataAcquisitionUI.h"

#include "TaskCardUi.h"
#include "TaskUi.h"
#include "CreateTaskUi.h"
#include<QApplication>
#include <QPushButton>  
#include <QVBoxLayout>  // 垂直布局
#include <QHBoxLayout>  // 水平布局
#include <QStackedWidget>  // 垂直或水平方向上排列页面，并且只会显示当前活动的页面
#include "ShowQRCode.h"

#define LENGTH 1200
#define HEIGHT 800

CloudDataAcquisitionUI& CloudDataAcquisitionUI::getInstance()
{
	static CloudDataAcquisitionUI cloudDataAcquisitionUI;
	return cloudDataAcquisitionUI;
}

CloudDataAcquisitionUI::CloudDataAcquisitionUI(QWidget* parent)
	: QWidget(parent)
{
	resize(LENGTH, HEIGHT);
	this->setWindowTitle(QString::fromLocal8Bit("网络数据提取管理工具"));
	initUi();
}

CloudDataAcquisitionUI::~CloudDataAcquisitionUI()
{}

void CloudDataAcquisitionUI::initUi()
{
	QVBoxLayout* mainlayout = new QVBoxLayout;
	mainlayout->setSpacing(0);
	mainlayout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(mainlayout);

	QWidget* topWidget = new QWidget;
	mainlayout->addWidget(topWidget);
	{
		QHBoxLayout* topLayout = new QHBoxLayout;
		topWidget->setLayout(topLayout);

		QWidget* taskWidget = new QWidget;
		taskWidget->setFixedSize(LENGTH, 100);
		taskWidget->setStyleSheet("#cloudDataAcquisitionUiWidget{border-bottom: 1px solid black;}");
		topLayout->addWidget(taskWidget);
		topLayout->setSpacing(0);
		topLayout->setContentsMargins(0, 0, 0, 0);
		{
			taskLayout = new QHBoxLayout;
			taskLayout->setContentsMargins(0, 0, 0, 0);
			taskWidget->setLayout(taskLayout);
			taskLayout->setSpacing(0);
			//taskLayout->setContentsMargins(0, 20, 40, 0);  // 左 上 右 下
			{
				pListBtn = new QPushButton;
				pListBtn->setFixedSize(100, 30);  // 设置按钮长宽
				pListBtn->setText(QString::fromLocal8Bit("任务列表"));
				QFont f1("仿宋", 12);
				pListBtn->setFont(f1);  // 设置按钮字体
				taskLayout->addWidget(pListBtn, 0, Qt::AlignLeft | Qt::AlignBottom); // 将按钮放在最左边底部
				taskLayout->addStretch();
				connect(pListBtn, &QPushButton::clicked, this, &CloudDataAcquisitionUI::showTaskList);
			}

			QHBoxLayout* createLayout = new QHBoxLayout;
			createLayout->setContentsMargins(0, 0, 0, 0);
			taskWidget->setLayout(taskLayout);
			taskLayout->setSpacing(0);
			{
				pAddBtn = new QPushButton();
				pAddBtn->setFixedSize(100, 30);
				pAddBtn->setText(QString::fromLocal8Bit("创建任务"));
				QFont f3("仿宋", 12);
				pAddBtn->setFont(f3);
				topLayout->addWidget(pAddBtn, 0, Qt::AlignVCenter | Qt::AlignRight);
				connect(pAddBtn, &QPushButton::clicked, this, &CloudDataAcquisitionUI::createTask);
			}
		}
	}

	{
		stackedWidget = new QStackedWidget(this);
		CTaskCardUi* cTaskCardUi = new CTaskCardUi;  // 任务列表展示页面
		stackedWidget->addWidget(cTaskCardUi);  // 将页面添加到堆叠窗口
		stackedWidget->setFixedSize(LENGTH, HEIGHT - 100);
		mainlayout->addWidget(stackedWidget);
	}
}

void CloudDataAcquisitionUI::createTask()
{
	CreateTaskUi* createTaskUi = new CreateTaskUi;
	createTaskUi->show();
}

void CloudDataAcquisitionUI::showTaskList()
{
	stackedWidget->setCurrentIndex(0);
}

void CloudDataAcquisitionUI::showTask()
{
	stackedWidget->setCurrentWidget(ButtontoTaskUiMap[(QPushButton*)sender()]);
}

void CloudDataAcquisitionUI::addTask()
{


	//加一个新的任务切换按钮
	QPushButton* taskBtn = new QPushButton(this);
	taskBtn->setFixedSize(100, 30);
	taskBtn->setText(QString::fromLocal8Bit("任务"));
	taskBtn->setFont(QFont("仿宋", 12));  // 设置按钮字体

	QLayoutItem* item = taskLayout->takeAt(taskLayout->count()-1);
	if (item)
	{
		delete item->widget(); // 释放弹簧所占用的控件内存
		delete item; // 删除布局项
	}

	// 将新按钮添加到布局中
	taskLayout->addWidget(taskBtn, 0, Qt::AlignLeft | Qt::AlignBottom); // 将按钮放在最左边底部

	taskLayout->addStretch();

	//在栈窗口部署一个新的界面UI
	TaskUi* newTaskUi = new TaskUi(this);
	stackedWidget->addWidget(newTaskUi);
	ButtontoTaskUiMap.insert({ taskBtn ,newTaskUi });

	// 设置父窗口的布局为新创建的水平布局
	connect(taskBtn, &QPushButton::clicked, this, &CloudDataAcquisitionUI::showTask);
}