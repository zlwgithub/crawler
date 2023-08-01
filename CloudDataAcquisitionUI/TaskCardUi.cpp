#include "TaskCardUi.h"
#define LENGTH 400
#define HEIGHT 400

//c--->c++-->qt-->3rd-->自己
#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>

CTaskCardUi::CTaskCardUi(QWidget* parent):
	CSubUIDialog(parent)
{
	resize(LENGTH, HEIGHT);
	initUi();
}

CTaskCardUi::~CTaskCardUi()
{
	//布局
	//放控件
	//调间距
}

void CTaskCardUi::paintEvent(QPaintEvent* event)
{
	/*QStyleOption opt;
	opt.init(this);

	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);*/
}

void CTaskCardUi::initUi()
{
	/*QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0, 0, 0, 0);
	this->setClientLayout(vLayout);

	QHBoxLayout* hLayout = new QHBoxLayout;
	vLayout->addLayout(hLayout);*/
	{
		// 总体布局：垂直布局，包含三层布局
		QVBoxLayout* vLayout = new QVBoxLayout;
		vLayout->setSpacing(0);
		vLayout->setContentsMargins(0, 0, 0, 0);  // 左、上、右、下
		this->setClientLayout(vLayout);
		// 1、第一层布局：水平布局，展示两张图片
		{
			QWidget* firstQW = new QWidget;
			// 设置QW的属性，样式
			firstQW->setFixedSize(LENGTH, 100);
			firstQW->setObjectName("taskCardUiFirstQW");
			firstQW->setStyleSheet("#taskCardUiFirstQW{border: 1px solid blue;}");
			vLayout->addWidget(firstQW);

			QHBoxLayout* hLayout_1 = new QHBoxLayout;
			hLayout_1->setSpacing(0);
			hLayout_1->setContentsMargins(10, 0, 50, 0);  // 左、上、右、下
			firstQW->setLayout(hLayout_1);
			{
				// 第一张图片展示
				{
					firstLayerLabel_1 = new QLabel("picture");  // 设置label的初始显示内容为picture
					firstLayerLabel_1->setObjectName("taskCardUiLabel_1");
					firstLayerLabel_1->setFixedSize(100, 100);  // 设置标签的大小
					firstLayerLabel_1->setStyleSheet("#taskCardUiLabel_1 { border: 1px solid red; }");  // 设置标签的样式
					// 设置图片
					QPixmap pixmap("./pic1.png");
					QPixmap scaledPixmap = pixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio);  // 设置图片的大小
					firstLayerLabel_1->setPixmap(scaledPixmap);
					hLayout_1->addWidget(firstLayerLabel_1);
					hLayout_1->setAlignment(firstLayerLabel_1, Qt::AlignLeft);  // 将图片靠左排列，不过要有效果，此代码必须放在addWidget()之后
				}

				// 第二张图片展示
				{
					firstLayerLabel_2 = new QLabel("picture");  // 设置label的初始显示内容为picture
					firstLayerLabel_2->setObjectName("taskCardUiLabel_2");
					firstLayerLabel_2->setFixedSize(100, 100);  // 设置标签的大小
					firstLayerLabel_2->setStyleSheet("#taskCardUiLabel_2 { border: 1px solid red; }");  // 设置标签的样式
					// 设置图片
					QPixmap pixmap("./pic1.png");
					QPixmap scaledPixmap = pixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio);  // 设置图片的大小
					firstLayerLabel_2->setPixmap(scaledPixmap);
					hLayout_1->addWidget(firstLayerLabel_2);
					hLayout_1->setAlignment(firstLayerLabel_2, Qt::AlignRight);
				}
			}
		}

		// 2、第二层布局：垂直布局，包含三个label和三个LineEdit
		{
			QWidget* secondQW = new QWidget;
			// 设置QW的属性，样式
			secondQW->setFixedHeight(200);
			secondQW->setFixedWidth(LENGTH);
			secondQW->setObjectName("taskCardUiSecondQW");
			// secondQW->setStyleSheet("#taskCardUiSecondQW{border: 1px solid black;}");
			vLayout->addWidget(secondQW);

			QVBoxLayout* vLayout_2 = new QVBoxLayout;
			vLayout_2->setSpacing(0);
			vLayout_2->setContentsMargins(10, 0, 10, 0);  // 左、上、右、下
			secondQW->setLayout(vLayout_2);
			// 每一个label和LineEdit是水平布局
			// 第一个label和LineEdit
			{
				QWidget* secondQW_1 = new QWidget;
				vLayout_2->addWidget(secondQW_1);

				QHBoxLayout* hLayout_21 = new QHBoxLayout;
				hLayout_21->setSpacing(20);
				secondQW_1->setLayout(hLayout_21);

				hLayout_21->addStretch();
				secondLayerLabel_1 = new QLabel(QString::fromLocal8Bit("任务名称："));
				hLayout_21->addWidget(secondLayerLabel_1);

				lineEdit_1 = new QLineEdit(QString::fromLocal8Bit("请输入任务的名称"));
				lineEdit_1->setFixedSize(200, 30);
				hLayout_21->addWidget(lineEdit_1);
				hLayout_21->addStretch();
			}
			// 第二个label和LineEdit
			{
				QWidget* secondQW_2 = new QWidget;
				vLayout_2->addWidget(secondQW_2);

				QHBoxLayout* hLayout_22 = new QHBoxLayout;
				hLayout_22->setSpacing(20);
				secondQW_2->setLayout(hLayout_22);

				hLayout_22->addStretch();
				secondLayerLabel_2 = new QLabel(QString::fromLocal8Bit("开始时间："));
				hLayout_22->addWidget(secondLayerLabel_2);

				lineEdit_2 = new QLineEdit(QString::fromLocal8Bit("请输入开始时间"));
				lineEdit_2->setFixedSize(200, 30);
				hLayout_22->addWidget(lineEdit_2);
				hLayout_22->addStretch();
			}
			// 第三个label和LineEdit
			{
				QWidget* secondQW_3 = new QWidget;
				vLayout_2->addWidget(secondQW_3);

				QHBoxLayout* hLayout_23 = new QHBoxLayout;
				hLayout_23->setSpacing(20);
				secondQW_3->setLayout(hLayout_23);

				hLayout_23->addStretch();
				secondLayerLabel_3 = new QLabel(QString::fromLocal8Bit("结束时间："));
				hLayout_23->addWidget(secondLayerLabel_3);

				lineEdit_3 = new QLineEdit(QString::fromLocal8Bit("请输入结束时间"));
				lineEdit_3->setFixedSize(200, 30);
				hLayout_23->addWidget(lineEdit_3);
				hLayout_23->addStretch();
			}
		}

		// 第三层布局：水平布局，包含两个按钮
		{
			QWidget* thirdQW = new QWidget;
			// 设置QW的属性，样式
			thirdQW->setFixedHeight(100);
			thirdQW->setFixedWidth(LENGTH);
			thirdQW->setObjectName("taskCardUiThirdQW");
			// thirdQW->setStyleSheet("#taskCardUiThirdQW{border: 1px solid black;}");
			vLayout->addWidget(thirdQW);

			QHBoxLayout* hLayout_3 = new QHBoxLayout;
			hLayout_3->setSpacing(0);
			hLayout_3->setContentsMargins(10, 0, 40, 0);  // 左、上、右、下
			thirdQW->setLayout(hLayout_3);
			// 开始任务按钮
			{
				startButton = new QPushButton(QString::fromLocal8Bit("开始任务"));
				startButton->setObjectName("taskCardUiStartButton");
				startButton->setFixedSize(100, 30);
				startButton->setStyleSheet("#taskCardUiStartButton{background-color:blue;color:red}");
				QFont f31("仿宋", 12);
				startButton->setFont(f31);
				hLayout_3->addWidget(startButton);
			}

			// 结束任务按钮
			{
				endButton = new QPushButton(QString::fromLocal8Bit("结束任务"));
				endButton->setObjectName("taskCardUiEndButton");
				endButton->setFixedSize(100, 30);
				endButton->setStyleSheet("#taskCardUiEndButton{background-color:blue;color:red}");
				QFont f32("仿宋", 12);
				endButton->setFont(f32);
				hLayout_3->addWidget(endButton);
			}
		}
		vLayout->addStretch();
	}
}
