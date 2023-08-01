#include "StartTaskUi.h"
#include "DisplayProgressUi.h"
#include "ShowResultsUi.h"
#define LENGTH 800

#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QCoreApplication>
#include<db.h>
#include<proxy.h>
#include"service.h"
CStartTaskUi::CStartTaskUi(QWidget* parent) :
	QWidget(parent)
{

	resize(LENGTH, 700);
	//setDialogTitle(QString::fromLocal8Bit("数据采集进度"));
	initUi();
	this->show();
}

CStartTaskUi::~CStartTaskUi()
{
}

void CStartTaskUi::paintEvent(QPaintEvent* event)
{
	/*QStyleOption opt;
	opt.init(this);

	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);*/
}

void CStartTaskUi::initUi()
{
	// 总体布局为垂直布局，共两层
	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0, 0, 0, 0);
	//this->setClientLayout(vLayout);

	// 第一层，总的是水平布局，分左右侧，左侧为垂直布局，右侧是一个按钮
	{
		QWidget* firstLayerQW = new QWidget;
		firstLayerQW->setObjectName("StrtTaskUiFirstLayerQW");
		firstLayerQW->setStyleSheet("#StrtTaskUiFirstLayerQW{border-bottom:1px solid red;}");
		firstLayerQW->setFixedSize(LENGTH, 150);
		vLayout->addWidget(firstLayerQW, 0, Qt::AlignTop);

		QHBoxLayout* hLayout_1 = new QHBoxLayout;
		hLayout_1->setSpacing(0);
		hLayout_1->setContentsMargins(0, 0, 90, 0);
		firstLayerQW->setLayout(hLayout_1);
		// 左侧垂直布局
		{
			QWidget* firstLeftQW = new QWidget;

			firstLeftQW->setFixedSize(LENGTH - 200, 150);
			hLayout_1->addWidget(firstLeftQW, 0, Qt::AlignLeft);

			QVBoxLayout* vLayout_1 = new QVBoxLayout;
			firstLeftQW->setLayout(vLayout_1);
			{
				// 总进度标签
				QLabel* totalProgressLabel = new QLabel(QString::fromLocal8Bit("总进度"));
				QFont f11("仿宋", 12);
				totalProgressLabel->setFont(f11);
				vLayout_1->addWidget(totalProgressLabel);

				// 进度条
				firstLayerProgressBar = new QProgressBar(this);
				firstLayerProgressBar->setFixedWidth(550);
				firstLayerProgressBar->setRange(0, 100); // 设置进度条的范围
				firstLayerProgressBar->setValue(0); // 设置进度条的初始值
				for (int i = 0; i <= 100; ++i) {
					firstLayerProgressBar->setValue(i);
					QCoreApplication::processEvents(); // 更新事件循环，以便进度条显示更新

					// 进行其他操作
				}
				vLayout_1->addWidget(firstLayerProgressBar);

				// 任务采集所用时间
				QHBoxLayout* hLayout_11 = new QHBoxLayout;
				vLayout_1->addLayout(hLayout_11);
				{
					QLabel* timeLabel = new QLabel(QString::fromLocal8Bit("任务采集所用时间："));
					QFont f21("仿宋", 12);
					timeLabel->setFont(f21);
					hLayout_11->addWidget(timeLabel);

					QLabel* showTimeLabel = new QLabel("30min");
					QFont f22("仿宋", 12);
					showTimeLabel->setFont(f22);
					hLayout_11->addWidget(showTimeLabel);
				}

				// 采集数据总数
				QHBoxLayout* hLayout_12 = new QHBoxLayout;
				vLayout_1->addLayout(hLayout_12);
				{
					QLabel* dataLabel = new QLabel(QString::fromLocal8Bit("采集数据总数："));
					QFont f31("仿宋", 12);
					dataLabel->setFont(f31);
					hLayout_12->addWidget(dataLabel);

					QLabel* showDataLabel = new QLabel("100");
					QFont f32("仿宋", 12);
					showDataLabel->setFont(f32);
					hLayout_12->addWidget(showDataLabel);
				}

			}
		}
		// 右侧的按钮
		{
			QPushButton* viewResultsBtn = new QPushButton(QString::fromLocal8Bit("查看结果"));
			QFont f12("仿宋", 12);
			viewResultsBtn->setFont(f12);
			viewResultsBtn->setFixedWidth(100);
			hLayout_1->addWidget(viewResultsBtn);

			connect(viewResultsBtn, &QPushButton::clicked, this, &CStartTaskUi::showResults);
			connect(viewResultsBtn, &QPushButton::clicked, this, &QWidget::close);
		}
	}

	// 第二层, 总的是水平布局，左侧是展示列表，右侧是滑动滚轮
	{
		QWidget* secondTotalLayerQW = new QWidget;  // 第二层总的布局，包括展示列表和滚动滑轮
		vLayout->addWidget(secondTotalLayerQW);

		QHBoxLayout* hSecondTotalLayout = new QHBoxLayout;
		secondTotalLayerQW->setLayout(hSecondTotalLayout);
		hSecondTotalLayout->setSpacing(0);
		hSecondTotalLayout->setContentsMargins(0, 0, 0, 0);
		{
			QListWidget* listView = new QListWidget(this);
			listView->setFlow(QListView::TopToBottom);

			hSecondTotalLayout->addWidget(listView);

			for (int i = 0; i < 10; ++i)
			{
				int iCount = listView->count();
				listView->insertItem(iCount + 1, "");

				QListWidgetItem* item = new QListWidgetItem;
				item->setSizeHint(QSize(LENGTH, 120));
				listView->addItem(item);

				CDisplayProgressUi* cDisplayProgressUi = new CDisplayProgressUi();
				listView->setItemWidget(item, cDisplayProgressUi);
			}
		}
	}

	connect(&Service::getInstance(), &Service::START_CRAWL_MSG_ACK_Signal, this, &CStartTaskUi::START_CRAWL_MSG_ACK_callback);
}

void CStartTaskUi::showResults()
{
	CShowResults *showresults = new CShowResults(this,dbname);
}


void CStartTaskUi::START_CRAWL_MSG_ACK_callback(QString qdbname)
{
	dbname = qdbname.toStdString();
	if (dbname.size())
	{
		LOG_INFO("爬取数据成功!");
		QMessageBox::information(this, " ", QString::fromLocal8Bit("爬取数据成功!"), QString::fromLocal8Bit("确认"));
	}
	else
	{
		LOG_INFO("爬取数据失败!");
		QMessageBox::information(this, " ", QString::fromLocal8Bit("爬取数据失败!"), QString::fromLocal8Bit("确认"));
	}
}

