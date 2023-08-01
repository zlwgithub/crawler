#include "TaskUi.h"
#include "StartTaskUi.h"
#define LENGTH 740
#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include<proxy.h>
#include <QtWidgets/qmessagebox.h>

TaskUi::TaskUi(QWidget* parent) :
	QWidget(parent)
{
	resize(LENGTH, 600);
	initUi();
}

TaskUi::~TaskUi()
{}


void TaskUi::initUi()
{
	// 总体布局：垂直布局，包含两层布局
	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0, 0, 0, 0);  // 左、上、右、下
	this->setLayout(vLayout);

	// 1、第一层布局：多个QWidget组成
	{
		QWidget* totalQW = new QWidget;
		totalQW->setFixedSize(LENGTH, 400);
		vLayout->addWidget(totalQW);

		QVBoxLayout* totalLayout = new QVBoxLayout;
		totalLayout->setSpacing(0);
		totalLayout->setContentsMargins(0, 0, 0, 10);  // 左、上、右、下
		totalQW->setLayout(totalLayout);
		// 每一个QWidget组成：垂直布局，上面部分包含：左边展示一张图片，右侧是垂直布局，包含三个信息：应用名称、账号、密码
		{
			QWidget* firstQW = new QWidget;
			// 设置QW的属性，样式
			firstQW->setFixedSize(LENGTH, 300);
			firstQW->setObjectName("taskCardUiFirstQW");
			// firstQW->setStyleSheet("#taskCardUiFirstQW{border: 1px solid blue;}");
			totalLayout->addWidget(firstQW);

			QHBoxLayout* hLayout_1 = new QHBoxLayout;
			hLayout_1->setSpacing(0);
			hLayout_1->setContentsMargins(10, 0, 10, 0);  // 左、上、右、下
			firstQW->setLayout(hLayout_1);
			// 展示左侧图片
			{
				firstLayerLabel_1 = new QLabel("picture");  // 设置label的初始显示内容为picture
				firstLayerLabel_1->setObjectName("taskCardUiLabel_1");
				firstLayerLabel_1->setFixedSize(350, 250);  // 设置标签的大小
				firstLayerLabel_1->setStyleSheet("#taskCardUiLabel_1 { border: 1px solid red; }");  // 设置标签的样式
				// 设置图片
				// QPixmap pixmap("./pic1.png");
				QPixmap pixmap("C:/Users/32447/Pictures/Saved Pictures/test.png");
				QPixmap scaledPixmap = pixmap.scaled(QSize(250, 250), Qt::KeepAspectRatio);  // 设置图片的大小
				firstLayerLabel_1->setPixmap(scaledPixmap);
				hLayout_1->addWidget(firstLayerLabel_1);
				hLayout_1->setAlignment(firstLayerLabel_1, Qt::AlignLeft);  // 将图片靠左排列，不过要有效果，此代码必须放在addWidget()之后	
			}
			// 右侧是垂直布局，包含三个信息：应用名称、账号、密码
			{
				QWidget* firstRightQW = new QWidget;
				// 设置QW的属性，样式
				firstRightQW->setFixedHeight(250);
				firstRightQW->setFixedWidth(350);
				firstRightQW->setObjectName("taskCardUiFirstRightQW");
				// firstRightQW->setStyleSheet("#taskCardUiFirstRightQW{border: 1px solid black;}");
				hLayout_1->addWidget(firstRightQW);

				QVBoxLayout* vLayout_1 = new QVBoxLayout;
				vLayout_1->setSpacing(0);
				vLayout_1->setContentsMargins(10, 0, 40, 0);  // 左、上、右、下
				firstRightQW->setLayout(vLayout_1);
				// 每一个label和LineEdit是水平布局
				// 第一个label和LineEdit
				{
					QWidget* firstRightQW_1 = new QWidget;
					vLayout_1->addWidget(firstRightQW_1);

					QHBoxLayout* hLayout_11 = new QHBoxLayout;
					hLayout_11->setSpacing(20);
					firstRightQW_1->setLayout(hLayout_11);

					hLayout_11->addStretch();
					secondLayerLabel_1 = new QLabel(QString::fromLocal8Bit("应用名称："));
					QFont f11("仿宋", 12);
					secondLayerLabel_1->setFont(f11);
					hLayout_11->addWidget(secondLayerLabel_1);

					lineEdit_1 = new QLineEdit(QString::fromLocal8Bit("XXXXXXXX"));
					lineEdit_1->setFixedSize(200, 30);
					hLayout_11->addWidget(lineEdit_1);
					hLayout_11->addStretch();
				}
				// 第二个label和LineEdit
				{
					QWidget* firstRightQW_2 = new QWidget;
					vLayout_1->addWidget(firstRightQW_2);

					QHBoxLayout* hLayout_12 = new QHBoxLayout;
					hLayout_12->setSpacing(20);
					firstRightQW_2->setLayout(hLayout_12);

					hLayout_12->addStretch();
					secondLayerLabel_2 = new QLabel(QString::fromLocal8Bit("账号："));
					QFont f12("仿宋", 12);
					secondLayerLabel_2->setFont(f12);
					hLayout_12->addWidget(secondLayerLabel_2);

					lineEdit_2 = new QLineEdit;
					lineEdit_2->setFixedSize(200, 30);
					hLayout_12->addWidget(lineEdit_2);
					hLayout_12->addStretch();
				}
				// 第三个label和LineEdit
				{
					QWidget* firstRightQW_3 = new QWidget;
					vLayout_1->addWidget(firstRightQW_3);

					QHBoxLayout* hLayout_13 = new QHBoxLayout;
					hLayout_13->setSpacing(20);
					firstRightQW_3->setLayout(hLayout_13);

					hLayout_13->addStretch();
					secondLayerLabel_3 = new QLabel(QString::fromLocal8Bit("密码："));
					QFont f13("仿宋", 12);
					secondLayerLabel_3->setFont(f13);
					hLayout_13->addWidget(secondLayerLabel_3);

					lineEdit_3 = new QLineEdit;
					lineEdit_3->setFixedSize(200, 30);
					hLayout_13->addWidget(lineEdit_3);
					hLayout_13->addStretch();
				}
			}
		}
		// 每一个QWidget的下面部分，包含：四个复选框
		{
			// 创建四个复选框
			QCheckBox* userInformationBox = new QCheckBox(QString::fromLocal8Bit("用户信息"));
			QCheckBox* contactsInformationBox = new QCheckBox(QString::fromLocal8Bit("联系人"));
			QCheckBox* messageInformationBox = new QCheckBox(QString::fromLocal8Bit("短信"));
			QCheckBox* otherInformationBox = new QCheckBox(QString::fromLocal8Bit("其他"));

			QFont f("仿宋", 12);
			userInformationBox->setFont(f);
			contactsInformationBox->setFont(f);
			messageInformationBox->setFont(f);
			otherInformationBox->setFont(f);

			QWidget* secondQW = new QWidget;
			secondQW->setObjectName("taskCardUisecondQW");
			secondQW->setStyleSheet("#taskCardUisecondQW{border: 1px solid black;}");
			secondQW->setFixedSize(LENGTH, 100);
			totalLayout->addWidget(secondQW);

			QVBoxLayout* vLayout_2 = new QVBoxLayout;
			{
				{
					QHBoxLayout* hLayout_21 = new QHBoxLayout;
					hLayout_21->addWidget(userInformationBox);
					hLayout_21->addWidget(contactsInformationBox);
					vLayout_2->addLayout(hLayout_21);
				}
				{
					QHBoxLayout* hLayout_22 = new QHBoxLayout;
					hLayout_22->addWidget(messageInformationBox);
					hLayout_22->addWidget(otherInformationBox);
					vLayout_2->addLayout(hLayout_22);
				}
			}
			secondQW->setLayout(vLayout_2);
		}
	}

	// 第二层布局：水平布局，包含一个按钮
	{
		QWidget* secondQW = new QWidget;
		// 设置QW的属性，样式
		secondQW->setFixedHeight(100);
		secondQW->setFixedWidth(LENGTH);
		secondQW->setObjectName("taskCardUisecondQW");
		secondQW->setStyleSheet("#taskCardUisecondQW{border-top: 1px solid black;}");
		vLayout->addWidget(secondQW);

		QHBoxLayout* hLayout_3 = new QHBoxLayout;
		hLayout_3->setSpacing(0);
		hLayout_3->setContentsMargins(10, 0, 40, 0);  // 左、上、右、下
		secondQW->setLayout(hLayout_3);
		// 开始任务按钮
		{
			startButton = new QPushButton(QString::fromLocal8Bit("开始任务"));
			startButton->setObjectName("taskCardUiStartButton");
			startButton->setFixedSize(100, 30);
			startButton->setStyleSheet("#taskCardUiStartButton{background-color:blue;color:red}");
			QFont f31("仿宋", 12);
			startButton->setFont(f31);
			hLayout_3->addWidget(startButton);

			connect(startButton, &QPushButton::clicked, this, &TaskUi::startTaskBtn);
			connect(startButton, &QPushButton::clicked, this, &QWidget::close);
		}
	}
	vLayout->addStretch();

}

void TaskUi::startTaskBtn()
{
	//通知爬虫开始爬取数据
	std::string s = "";
	Proxy::getInstance().send(MsgType::START_CRAWL_MSG, s);
	CStartTaskUi* StartTaskUi = new CStartTaskUi(nullptr);
	StartTaskUi->show();
}
