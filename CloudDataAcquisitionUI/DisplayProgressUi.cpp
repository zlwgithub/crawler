#include "DisplayProgressUi.h"
#define LENGTH 800

#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QCoreApplication>

CDisplayProgressUi::CDisplayProgressUi(QWidget* parent) :
	CSubUIDialog(parent)
{
	resize(LENGTH, 120);
	initUi();
}

CDisplayProgressUi::~CDisplayProgressUi()
{
}

void CDisplayProgressUi::paintEvent(QPaintEvent* event)
{
	/*QStyleOption opt;
	opt.init(this);

	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);*/
}

void CDisplayProgressUi::initUi()
{
	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0, 0, 0, 0);
	this->setClientLayout(vLayout);

	QHBoxLayout* hLayout = new QHBoxLayout;
	vLayout->addLayout(hLayout);

	// 总体布局是水平布局，分左右两侧，左侧是一张图片，右侧是垂直布局
	{
		QWidget* secondLayerQW = new QWidget;
		secondLayerQW->setObjectName("StartTaskUiSecondLayerQW");
		secondLayerQW->setStyleSheet("#StartTaskUiSecondLayerQW{border: 1px solid red;}");
		hLayout->addWidget(secondLayerQW);

		QHBoxLayout* hLayout_2 = new QHBoxLayout;
		hLayout_2->setSpacing(0);
		hLayout_2->setContentsMargins(10, 10, 0, 0);
		secondLayerQW->setLayout(hLayout_2);
		// 左侧图片
		{
			QLabel* label_2 = new QLabel;
			label_2->setObjectName("obj1");
			label_2->setStyleSheet("#obj1{border:1px solid black;}");
			QPixmap pixmap("./pic1.png");
			QPixmap scaledPixmap = pixmap.scaled(QSize(120, 120), Qt::KeepAspectRatio);  // 设置图片的大小
			label_2->setPixmap(scaledPixmap);
			hLayout_2->addWidget(label_2);
			hLayout_2->setAlignment(label_2, Qt::AlignLeft | Qt::AlignTop);
		}
		// 右侧是垂直布局，共四层
		{
			QVBoxLayout* vLayout_21 = new QVBoxLayout;
			vLayout_21->setContentsMargins(50, 0, 0, 0);
			hLayout_2->addLayout(vLayout_21);
			// 垂直布局的第一层，水平布局
			{
				QHBoxLayout* hLayout_21 = new QHBoxLayout;
				hLayout_21->setSpacing(0);
				vLayout_21->addLayout(hLayout_21);

				QLabel* applicationLabel = new QLabel(QString::fromLocal8Bit("应用："));
				applicationLabel->setFixedSize(100, 25);
				hLayout_21->addWidget(applicationLabel);

				QLabel* showApplicationLabel = new QLabel(QString::fromLocal8Bit("XXXX"));
				showApplicationLabel->setFixedSize(100, 25);
				hLayout_21->addWidget(showApplicationLabel);

				QLabel* startTime = new QLabel(QString::fromLocal8Bit("开始时间："));
				startTime->setFixedSize(100, 25);
				hLayout_21->addWidget(startTime);

				QLabel* showStartTime = new QLabel(QString::fromLocal8Bit("XXXX"));
				startTime->setFixedSize(100, 25);
				hLayout_21->addWidget(showStartTime);

			}
			// 垂直布局的第二层，水平布局
			{
				QHBoxLayout* hLayout_22 = new QHBoxLayout;
				vLayout_21->addLayout(hLayout_22);

				QLabel* accountNumberLabel = new QLabel(QString::fromLocal8Bit("账号："));
				accountNumberLabel->setFixedSize(100, 25);
				hLayout_22->addWidget(accountNumberLabel);

				QLabel* showAccountNumberLabel = new QLabel(QString::fromLocal8Bit("XXXX"));
				showAccountNumberLabel->setFixedSize(100, 25);
				hLayout_22->addWidget(showAccountNumberLabel);

				QLabel* useTime = new QLabel(QString::fromLocal8Bit("所花时间："));
				useTime->setFixedSize(100, 25);
				hLayout_22->addWidget(useTime);

				QLabel* showUseTime = new QLabel(QString::fromLocal8Bit("XXXX"));
				showUseTime->setFixedSize(100, 25);
				hLayout_22->addWidget(showUseTime);
				hLayout_22->addStretch();
			}
			// 垂直布局第三层， 两个label
			{
				QHBoxLayout* hLayout_23 = new QHBoxLayout;
				vLayout_21->addLayout(hLayout_23);

				QLabel* collectLogsLabel = new QLabel(QString::fromLocal8Bit("采集日志："));
				collectLogsLabel->setFixedSize(100, 25);
				hLayout_23->addWidget(collectLogsLabel);

				QLabel* showCollectLogsLabel = new QLabel(QString::fromLocal8Bit("正在登陆"));
				showCollectLogsLabel->setFixedSize(100, 25);
				hLayout_23->addWidget(showCollectLogsLabel);
				hLayout_23->addStretch();
			}
			// 垂直布局第四层， 进度条
			{
				secondLayerProgressBar = new QProgressBar(this);
				secondLayerProgressBar->setFixedSize(450, 25);
				secondLayerProgressBar->setRange(0, 100); // 设置进度条的范围
				secondLayerProgressBar->setValue(0); // 设置进度条的初始值
				for (int i = 0; i <= 100; ++i)
				{
					secondLayerProgressBar->setValue(i);
					QCoreApplication::processEvents(); // 更新事件循环，以便进度条显示更新

					// 进行其他操作
				}
				vLayout_21->addWidget(secondLayerProgressBar);
			}
		}
		hLayout_2->addStretch();
	}
}