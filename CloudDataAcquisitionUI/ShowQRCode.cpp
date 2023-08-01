#include "ShowQRCode.h"
#include<proxy.h>
#include <iostream>
#include "StartTaskUi.h"
#include "TaskUi.h"
#include<qdebug.h>
#include"service.h"
using namespace std;

CShowQRCode::CShowQRCode(QWidget* parent)
	: QWidget(parent)
{
	this->setWindowTitle(QString::fromLocal8Bit("扫描二维码"));
	resize(600 + 30, 700 + 30);

	auto layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(layout);

	// 创建主窗口
	mainWidget = new QWidget;
	mainWidget->resize(400, 500);
	layout->addWidget(mainWidget);

	// 创建 QLabel 来显示图片
	imagelabel = new QLabel;
	AttentionLabel = new QLabel;
	Label1 = new QLabel;
	Label2 = new QLabel;

	// 创建按钮
	commitButton = new QPushButton(QString::fromLocal8Bit("确认"));
	commitButton->setFixedSize(100, 30);

	// 设置文字信息
	AttentionLabel->setText(QString::fromLocal8Bit("注意："));
	Label1->setText(QString::fromLocal8Bit("1.请使用手机QQ扫描二维码并确认；"));
	Label2->setText(QString::fromLocal8Bit("2.点击窗口上的确定按钮"));



	// 设置样式
	mainWidget->setStyleSheet(
		"QWidget {"
		"background-color: #f0f0f0;"
		"}"
	); // 设置背景颜色为浅灰色

	AttentionLabel->setStyleSheet(
		"QLabel {"
		"font-weight: bold;"
		"color: #007bff;" // 设置文字颜色为蓝色
		"}"
	);

	commitButton->setStyleSheet(
		// 普通状态下的样式
		"QPushButton {"
		"font-family: \"Microsoft YaHei\";" // 字体为微软雅黑
		"font-style: normal;" // 字体风格为普通
		"font-weight: 400;" // 字体粗细为正常
		"font-size: 14px;" // 字体大小为14px
		"text-decoration: none;" // 文本装饰为无
		"color: #ffffff;" // 文本颜色为白色
		"border: none;" // 去除按钮边框
		"border-radius: 4px;" // 设置按钮边框的圆角半径为4px
		"background-color: #2074f3;" // 设置按钮背景色为蓝色
		"}"

		// 鼠标悬停时的样式
		"QPushButton:hover {"
		"background-color: #629df7;" // 设置鼠标悬停时按钮背景色为深蓝色
		"}"

		// 按钮按下时的样式
		"QPushButton:pressed {"
		"background-color: #1a5dc2;" // 设置按钮按下时背景色为更深的蓝色
		"}"
	);


	// 垂直布局
	mainLayout = new QVBoxLayout;
	mainLayout->setAlignment(Qt::AlignCenter); // 设置内容在中心对齐

	// 创建水平布局用于居中按钮
	buttonLayout = new QHBoxLayout;
	buttonLayout->addStretch(); // 添加伸缩项，使按钮居中
	buttonLayout->addWidget(commitButton);
	buttonLayout->addStretch(); // 添加伸缩项，使按钮居中

	// 添加控件到主布局
	mainLayout->addWidget(imagelabel);
	mainLayout->addWidget(AttentionLabel);
	mainLayout->addWidget(Label1);
	mainLayout->addWidget(Label2);
	mainLayout->addSpacing(20); // 在垂直布局中，添加高度为20的间距
	mainLayout->addLayout(buttonLayout);

	// 设置边距和间距
	mainLayout->setContentsMargins(30, 30, 30, 30); // 设置边距
	mainLayout->setSpacing(20); // 设置布局中的间距

	// 将主布局设置为主窗口的布局
	mainWidget->setLayout(mainLayout);

	// 连接按钮点击信号与槽函数
	connect(commitButton, &QPushButton::clicked, this, &CShowQRCode::Popup_Scan);
	connect(commitButton, &QPushButton::clicked, this, &QWidget::close);

	connect(&Service::getInstance(), &Service::QRCODE_CONFIRM_MSG_ACK_Signal, this, &CShowQRCode::QRCODE_CONFIRM_MSG_ACK_callback);
}

CShowQRCode::~CShowQRCode()
{}

// 扫描二维码槽函数
void CShowQRCode::Popup_Scan()
{
	std::string s = "";
	Proxy::getInstance().send(MsgType::QRCODE_CONFIRM_MSG, s);
}

void CShowQRCode::showqrcode(std::string image_path)
{
	// 创建 QPixmap 对象并加载图片
	QrCode = new QPixmap(image_path.c_str());
	// 检查是否成功加载图片
	if (QrCode->isNull()) {
		LOG_ERROR("无法加载图片:%s!", image_path.c_str());
		return;
	}

	// 调整图片大小以适应边框大小
	QSize imageSize(300, 300); // 设置目标宽度和高度
	*QrCode = QrCode->scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

	// 将 QPixmap 对象设置为 QLabel 的内容
	imagelabel->setPixmap(*QrCode);
	//show();open();//exec()
	this->show();
}

void CShowQRCode::QRCODE_CONFIRM_MSG_ACK_callback(QString qloginres)
{
	/*QMessageBox::information(this, " ", QString::fromLocal8Bit("爬取成功!"), QString::fromLocal8Bit("确认"));
	CStartTaskUi StarTtask;
	StarTtask.exec();
	this->accept();*/
	std::string loginres = qloginres.toStdString();
	if (loginres == "true")
	{
		QMessageBox::information(this, " ", QString::fromLocal8Bit("登录成功!"), QString::fromLocal8Bit("确认"));
		TaskUi * FirstTask = new TaskUi(nullptr);
		FirstTask->show();
	}
	else
	{
		QMessageBox::information(this, " ", QString::fromLocal8Bit("登录失败!"), QString::fromLocal8Bit("确认"));
	}
}