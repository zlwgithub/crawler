#include "CreateTaskUi.h"
#include "StartTaskUi.h"

#define LENGTH 600
#define HEIGHT 50

#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QString>
#include<public.h>
#include"CloudDataAcquisitionUI.h"
#include "ShowQRCode.h"
#include"service.h"
#include"qprocess.h"
CreateTaskUi::CreateTaskUi(QWidget* parent) :
	QWidget(parent)
{
	resize(LENGTH, 450);
	this->setWindowTitle(QString::fromLocal8Bit("创建任务"));
	initUi();
}

CreateTaskUi::~CreateTaskUi()
{}


void CreateTaskUi::initUi()
{
	// 总体布局为垂直布局，共两层
	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(vLayout);

	// 第一层布局：垂直布局，共三层，每一层包含一个Label和LineEdit
	{
		QWidget* firstQW = new QWidget;
		firstQW->setFixedSize(LENGTH, 300);
		vLayout->addWidget(firstQW);

		QVBoxLayout* vFirstLayout = new QVBoxLayout;
		vFirstLayout->setSpacing(0);
		vFirstLayout->setContentsMargins(0, 0, 0, 0);
		firstQW->setLayout(vFirstLayout);
		{
			// 第一个Label和LineEdit
			{
				QWidget* secondQW_1 = new QWidget;
				secondQW_1->setFixedSize(LENGTH, HEIGHT);
				vFirstLayout->addWidget(secondQW_1);

				QHBoxLayout* hLayout_1 = new QHBoxLayout;
				secondQW_1->setLayout(hLayout_1);

				hLayout_1->addStretch();
				firstLayerLabel_1 = new QLabel(QString::fromLocal8Bit("任务名称："));
				QFont f1("仿宋", 12);
				firstLayerLabel_1->setFont(f1);
				hLayout_1->addWidget(firstLayerLabel_1);
				lineEdit_1 = new QLineEdit(QString::fromLocal8Bit("请输入任务名称"));
				lineEdit_1->setFixedWidth(300);
				hLayout_1->addWidget(lineEdit_1);
				hLayout_1->addStretch();
			}
			// 第二个Label和LineEdit
			{
				QWidget* secondQW_2 = new QWidget;
				secondQW_2->setFixedSize(LENGTH, HEIGHT);
				vFirstLayout->addWidget(secondQW_2);

				QHBoxLayout* hLayout_2 = new QHBoxLayout;
				secondQW_2->setLayout(hLayout_2);

				hLayout_2->addStretch();
				firstLayerLabel_2 = new QLabel(QString::fromLocal8Bit("创建者谁："));
				QFont f2("仿宋", 12);
				firstLayerLabel_2->setFont(f2);
				hLayout_2->addWidget(firstLayerLabel_2);
				lineEdit_2 = new QLineEdit(QString::fromLocal8Bit("请输入创建者姓名"));
				lineEdit_2->setFixedWidth(300);
				hLayout_2->addWidget(lineEdit_2);
				hLayout_2->addStretch();
			}
			// 第三个Label和LineEdit
			{
				QWidget* secondQW_3 = new QWidget;
				secondQW_3->setFixedSize(LENGTH, HEIGHT);
				vFirstLayout->addWidget(secondQW_3);

				QHBoxLayout* hLayout_3 = new QHBoxLayout;
				secondQW_3->setLayout(hLayout_3);

				hLayout_3->addStretch();
				firstLayerLabel_3 = new QLabel(QString::fromLocal8Bit("任务编号："));
				QFont f3("仿宋", 12);
				firstLayerLabel_3->setFont(f3);
				hLayout_3->addWidget(firstLayerLabel_3);
				lineEdit_3 = new QLineEdit(QString::fromLocal8Bit("请输入任务编号"));
				lineEdit_3->setFixedWidth(300);
				hLayout_3->addWidget(lineEdit_3);
				hLayout_3->addStretch();
			}
		}
	}

	// 第二层布局，包含一个按钮
	{
		QHBoxLayout* secondLayerLayout = new QHBoxLayout;
		QPushButton* confireBtn = new QPushButton(QString::fromLocal8Bit("确认"));
		QFont f1("仿宋", 12);
		confireBtn->setFont(f1);  // 设置按钮字体
		confireBtn->setFixedSize(100, 60);
		secondLayerLayout->addStretch();
		secondLayerLayout->addWidget(confireBtn);
		secondLayerLayout->addStretch();
		vLayout->addLayout(secondLayerLayout);

		connect(confireBtn, &QPushButton::clicked, this, &CreateTaskUi::saveToDB);
		connect(confireBtn, &QPushButton::clicked, this, &QWidget::close);
		connect(confireBtn, &QPushButton::clicked, this, &CreateTaskUi::sendUrl);
		connect(confireBtn, &QPushButton::clicked, this, &CreateTaskUi::addTask);
		connect(confireBtn, &QPushButton::clicked, this, &CreateTaskUi::startTask);

		connect(&Service::getInstance(), &Service::GET_QRCODE_MSG_ACK_Signal, this, &CreateTaskUi::GET_QRCODE_MSG_ACK_callback);
	}
}


void CreateTaskUi::GET_QRCODE_MSG_ACK_callback(QString image_path)
{
	CShowQRCode* cShowQRCode = new CShowQRCode(nullptr);
	cShowQRCode->showqrcode(image_path.toStdString());
}

void CreateTaskUi::sendUrl()
{
	std::string url = lineEdit_1->text().toStdString();
	Proxy::getInstance().send(MsgType::GET_QRCODE_MSG, url);
}

void CreateTaskUi::addTask()
{
	CloudDataAcquisitionUI::getInstance().addTask();
}

void CreateTaskUi::startTask()
{
	//创建子线程 执行爬虫程序   子线程和主线程分别连接redis服务器发布订阅端口   消息通信，终止子线程特殊消息
	 
	CloudDataAcquisitionUI::getInstance().addTask();
}

void CreateTaskUi::saveToDB()
{
	QString TaskUrl = lineEdit_1->text();
	QString Creater = lineEdit_2->text();
	QString TaskId = lineEdit_3->text();
	// 连接数据库
	QSqlDatabase database;
	database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("MyDataBase.db");
	// 打开数据库
	database.open();

	QSqlQuery sql_query;
	// 第一种添加方式
	QString insert_sql = "insert into CreateTaskTable values (?, ?, ?)";
	sql_query.prepare(insert_sql);
	sql_query.addBindValue(TaskUrl);
	sql_query.addBindValue(Creater);
	sql_query.addBindValue(TaskId);
	sql_query.exec();

//	QProcess p;
//	QStringList list;
//	list.push_back("xxxx\.exe");
//	list.push_back("1");
//	list.push_back("json");
//	p.setArguments(list);
//	p.start();
//	p.waitForStarted();
//	p.processId();
//
//cmd:  "taskkill /F /ID processname";
//
//	QStringList args;
//	args << "/F";
//	args << "/IM testApp.exe";
//	//taskkill /pid 2604 -t -f
//	QProcess::execute("taskkill", args); //Should be 'taskkill /IM testApp.exe /F'
}
//connect


//void func()
//{
//
//}
