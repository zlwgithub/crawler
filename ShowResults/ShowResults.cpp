#include "ShowResults.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QScrollArea>
#include <iostream>
using namespace std;

ShowResults::ShowResults(QWidget* parent = nullptr, vector<std::string> vec = {})
    : QWidget(parent)
{
    ui.setupUi(this);
	int colsize = vec.size();
	// 创建主窗口
	mainWindow = new QWidget;
	mainWindow->setWindowTitle("QQ同步助手界面");//设置了窗口标题为 "QQ同步助手界面"
	mainWindow->resize(800, 500);//窗口大小设置为宽度 800 高度 500 

	// 创建左侧目录树
	treeWidget = new QTreeWidget;
	treeWidget->setHeaderLabel("目录");//设置目录树的头部标签为 "目录"

	// FontAwesome字体图标
	QFont fontAwesomeFont("FontAwesome");
	fontAwesomeFont.setPointSize(12); // 设置字体大小
	treeWidget->setFont(fontAwesomeFont); // 设置字体

	// 创建根节点和子节点，使用FontAwesome字体图标
	 //rootItem = new QTreeWidgetItem(treeWidget, QStringList() << "QQ同步助手");
	 //qqNumberItem = new QTreeWidgetItem(rootItem, QStringList() << " QQ号码");
	 //userInfoItem = new QTreeWidgetItem(qqNumberItem, QStringList() << " 用户信息");
	 //contactsItem = new QTreeWidgetItem(qqNumberItem, QStringList() << " 联系人");
	 //messagesItem = new QTreeWidgetItem(qqNumberItem, QStringList() << " 短信");
	 //photosItem = new QTreeWidgetItem(qqNumberItem, QStringList() << " 相册");
	 //otherItem = new QTreeWidgetItem(qqNumberItem, QStringList() << " 其他");
	//将目录树中的所有节点都展开，使得所有节点都可见。
	treeWidget->expandAll();

	// 创建右侧表格
	tableWidget = new QTableWidget;

	tableWidget->setColumnCount(colsize);//设置了表格的列数为 8

	auto qlist = QStringList();
	for (auto a : vec)
	{
		qlist << a.c_str();
	}
	//设置水平表头标签
	tableWidget->setHorizontalHeaderLabels(qlist);
	tableWidget->setHorizontalHeaderLabels(QStringList() << "姓名" << "描述" << "出生日期" << "电话" << "邮箱" << "qq" << "公司" << "职位");
	tableWidget->setRowCount(0); // 假设有20条目，超出显示区域时可以滚动查看
	//获取表格行数，为了初始化 currentRowCount
	currentRowCount = tableWidget->rowCount();

	// 设置表格样式
	tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #f0f0f0; }"); // 表头背景色，灰色
	

	//设置左侧目录树表格的样式
	applyStyles();


	// 将表格放置在QScrollArea中
	scrollArea = new QScrollArea;
	//通过 scrollArea.setWidgetResizable(true) 将 QScrollArea 设置为自适应大小
	//，以便能够根据表格大小自动调整滚动区域的大小。
	scrollArea->setWidgetResizable(true);
	//通过 scrollArea.setWidget(&tableWidget) 将表格设置为 QScrollArea 的子部件
	scrollArea->setWidget(tableWidget);

	// 设置布局
	QVBoxLayout* leftLayout = new QVBoxLayout;
	QVBoxLayout* rightLayout = new QVBoxLayout;
	leftLayout->addWidget(treeWidget);//将目录树 treeWidget 放置在左侧布局
	rightLayout->addWidget(scrollArea);//将包含表格的滚动区域 scrollArea 放置在右侧布局 

	// 创建一个水平布局用于包裹左右两侧布局
	mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout, 1); // 设置左侧布局的拉伸因子为1
	mainLayout->addSpacing(30); // 添加水平间距
	mainLayout->addLayout(rightLayout, 3); // 设置右侧布局的拉伸因子为2

	mainWindow->setLayout(mainLayout);


	connect(treeWidget, &QTreeWidget::itemClicked, this, &ShowResults::onItemClicked);


}

ShowResults::~ShowResults()
{}
void ShowResults::show()
{
	mainWindow->show();
}

//显示结果槽函数
void ShowResults::onItemClicked(QTreeWidgetItem* item, int column)
{
	//// 获取点击的项的文本
	//QString text = item->text(column);

	//// 根据文本切换到相应的视图界面
	//if (text == "QQ号码")
	//{
	//	// 切换到QQ号码视图界面
	//	// ...
	//}
	//else if (text == "用户信息")
	//{
	//	// 切换到用户信息视图界面
	//	// ...
	//}
	//else if (text == "联系人")
	//{
	//	// 切换到联系人视图界面
	//	// ...
	//}
	

}



// 将数据添加到表格的函数，接收一个指向 QTableWidget 的指针作为参数
//void ShowResults::addDataToTable(QTableWidget* tableWidget, const QString& 姓名, const QString& 描述, const QString& 出生日期,
//	const QString& 电话, const QString& 邮箱, const QString& QQ,
//	const QString& 公司, const QString& 职位)
//{
//	// 获取当前表格的行数
//	//int currentRowCount = tableWidget->rowCount();
//
//	// 在表格末尾插入一行
//	if (tableWidget != nullptr)
//	{
//		tableWidget->insertRow(currentRowCount);
//	}
//
//
//
//	// 创建新的QTableWidgetItem，并设置它们的文本内容
//	QTableWidgetItem* newItem1 = new QTableWidgetItem(姓名);
//	QTableWidgetItem* newItem2 = new QTableWidgetItem(描述);
//	QTableWidgetItem* newItem3 = new QTableWidgetItem(出生日期);
//	QTableWidgetItem* newItem4 = new QTableWidgetItem(电话);
//	QTableWidgetItem* newItem5 = new QTableWidgetItem(邮箱);
//	QTableWidgetItem* newItem6 = new QTableWidgetItem(QQ);
//	QTableWidgetItem* newItem7 = new QTableWidgetItem(公司);
//	QTableWidgetItem* newItem8 = new QTableWidgetItem(职位);
//
//	// 将新的QTableWidgetItem添加到表格中
//	if (tableWidget != nullptr)
//	{
//		tableWidget->setItem(currentRowCount, 0, newItem1);
//	}
//	if (tableWidget != nullptr)
//	{
//		tableWidget->setItem(currentRowCount, 1, newItem2);
//	}
//	if (tableWidget != nullptr)
//	{
//		tableWidget->setItem(currentRowCount, 2, newItem3);
//	}
//	if (tableWidget != nullptr)
//	{
//		tableWidget->setItem(currentRowCount, 3, newItem4);
//	}
//	if (tableWidget != nullptr)
//	{
//		tableWidget->setItem(currentRowCount, 4, newItem5);
//	}
//	if (tableWidget != nullptr)
//	{
//		tableWidget->setItem(currentRowCount, 5, newItem6);
//	}
//	if (tableWidget != nullptr)
//	{
//		tableWidget->setItem(currentRowCount, 6, newItem7);
//	}
//	if (tableWidget != nullptr)
//	{
//		tableWidget->setItem(currentRowCount, 7, newItem8);
//	}
//	/*
//	tableWidget->setItem(currentRowCount, 1, newItem2);
//	tableWidget->setItem(currentRowCount, 2, newItem3);
//	tableWidget->setItem(currentRowCount, 3, newItem4);
//	tableWidget->setItem(currentRowCount, 4, newItem5);
//	tableWidget->setItem(currentRowCount, 5, newItem6);
//	tableWidget->setItem(currentRowCount, 6, newItem7);
//	tableWidget->setItem(currentRowCount, 7, newItem8);
//	*/
//
//	//更新行数
//	currentRowCount++;
//
//}

//用于设置整体界面的样式和字体
void ShowResults::applyStyles()
{
	// 设置主窗口背景色
	setStyleSheet("background-color: #f0f0f0;");

	// 设置左侧目录树的样式
	treeWidget->setStyleSheet(
		"QTreeWidget {"
		"background-color: #ffffff;" // 白色背景
		"border: 1px solid #d0d0d0;" // 灰色边框
		"}"
		"QTreeWidget::item {"
		"height: 25px;" // 调整项的高度
		"padding-left: 0px;" // 左边距
		"}"
		"QTreeWidget::item:selected {"
		"background-color: #007bff;" // 选中项背景色，蓝色
		"color: #ffffff;" // 选中项文字颜色，白色
		"}"
	);




}
