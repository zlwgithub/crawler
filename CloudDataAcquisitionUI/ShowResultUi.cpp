#include "ShowResultsUi.h"

using namespace std;


//处理数据库的查询结果
int callback(void* data, int argc, char** argv, char** azColName)
{
	CShowResults* ShowResults = (CShowResults*)data;
	if (ShowResults->cur == 0)
	{
		Pqq* pqq = new Pqq;
		pqq->scrollArea = new QScrollArea;
		pqq->tableWidget = new QTableWidget;
		pqq->scrollArea->setWidget(pqq->tableWidget);
		auto qlist = QStringList();
		for (int i = 0; i < argc; ++i)
		{
			qlist << azColName[i];
		}
		pqq->tableWidget->setColumnCount(argc);//设置了表格的列数为 8
		pqq->tableWidget->setHorizontalHeaderLabels(qlist);
		//pqq->tableWidget->setRowCount(0); // 假设有20条目，超出显示区域时可以滚动查看
		pqq->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #f0f0f0; }"); // 表头背景色，灰色
		pqq->scrollArea->setWidgetResizable(true);
		ShowResults->qsvec.push_back(pqq);
	}
	addDataToTable(ShowResults->qsvec.back()->tableWidget, argc, argv);
	ShowResults->cur++;
	return 0;
}


CShowResults::CShowResults(QWidget* parent, std::string dbpath)
	: CUIDialog(parent)
{
	cur = 0;
	// 创建主窗口
	mainWindow = new QWidget;
	mainWindow->setWindowTitle(QString::fromLocal8Bit("QQ同步助手界面"));//设置了窗口标题为 "QQ同步助手界面"
	mainWindow->resize(800, 500);//窗口大小设置为宽度 800 高度 500 

	// 创建左侧目录树
	treeWidget = new QTreeWidget;
	treeWidget->setHeaderLabel(QString::fromLocal8Bit("目录"));//设置目录树的头部标签为 "目录"
	// FontAwesome字体图标
	QFont fontAwesomeFont("FontAwesome");
	fontAwesomeFont.setPointSize(12); // 设置字体大小
	treeWidget->setFont(fontAwesomeFont); // 设置字体
	// 创建根节点和子节点，使用FontAwesome字体图标
	rootItem = new QTreeWidgetItem(treeWidget, QStringList() << QString::fromLocal8Bit(" QQ同步助手"));
	qqNumberItem = new QTreeWidgetItem(rootItem, QStringList() << QString::fromLocal8Bit(" QQ号码"));
	userInfoItem = new QTreeWidgetItem(qqNumberItem, QStringList() << QString::fromLocal8Bit(" 用户信息"));
	contactsItem = new QTreeWidgetItem(qqNumberItem, QStringList() << QString::fromLocal8Bit(" 联系人"));
	messagesItem = new QTreeWidgetItem(qqNumberItem, QStringList() << QString::fromLocal8Bit(" 短信"));
	photosItem = new QTreeWidgetItem(qqNumberItem, QStringList() << QString::fromLocal8Bit(" 相册"));
	otherItem = new QTreeWidgetItem(qqNumberItem, QStringList() << QString::fromLocal8Bit(" 其他"));
	//将目录树中的所有节点都展开，使得所有节点都可见。
	treeWidget->expandAll();
	//设置左侧目录树表格的样式
	applyStyles();



	////查询数据库 并建立表格
	SqlRes sqlres;
	sqliteDb sqlitedb;
	sqlres = sqlitedb.InitDB(dbpath.c_str(), false);
	if (sqlres.errnum == 0)
	{
		LOG_INFO("打开数据库成功");
	}
	else
	{
		LOG_ERROR("打开数据库失败");
	}
	sqlitedb.setDQLCallBack(callback);
	string sql = "select * from contacts;";
	sqlitedb.do_sql(sql.c_str(), this);
	sqlitedb.close();


	//stackedWidget = QSharedPointer<QStackedWidget>(new QStackedWidget);
	//for (auto& a : qsvec)
	//{
	//	stackedWidget->addWidget(a->scrollArea);
	//}

	leftLayout = new QVBoxLayout;
	rightLayout = new QVBoxLayout;
	leftLayout->addWidget(treeWidget);//将目录树 treeWidget 放置在左侧布局
	rightLayout->addWidget(qsvec.back()->scrollArea);//将包含表格的滚动区域 scrollArea 放置在右侧布局 

	// 创建一个水平布局用于包裹左右两侧布局
	mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout, 1); // 设置左侧布局的拉伸因子为1
	mainLayout->addSpacing(30); // 添加水平间距
	mainLayout->addLayout(rightLayout, 3); // 设置右侧布局的拉伸因子为2
	mainWindow->setLayout(mainLayout);
	mainWindow->show();
	connect(treeWidget, &QTreeWidget::itemClicked, this, &CShowResults::onItemClicked);

}

CShowResults::~CShowResults()
{}

//显示结果槽函数
void CShowResults::onItemClicked(QTreeWidgetItem* item, int column)
{
	//item->
	// 获取点击的项的文本
	QString text = item->text(column);

	// 根据文本切换到相应的视图界面
	if (text == "QQ号码")
	{
		// 切换到QQ号码视图界面
		// ...
	}
	else if (text == "用户信息")
	{
		stackedWidget->setCurrentIndex(0);
	}
	else if (text == "联系人")
	{
		stackedWidget->setCurrentIndex(1);
	}
	else if (text == "短信")
	{
		stackedWidget->setCurrentIndex(2);
	}
	else if (text == "相册")
	{
		stackedWidget->setCurrentIndex(3);
	}
	else if (text == "其他")
	{
		stackedWidget->setCurrentIndex(4);
	}
	// 添加其他切换逻辑
}


// 将数据添加到表格的函数，接收一个指向 QTableWidget 的指针作为参数
void addDataToTable(QTableWidget* tableWidget, int argc, char** argv)
{
	// 获取当前表格的行数
	int currentRowCount = tableWidget->rowCount();

	// 在表格末尾插入一行
	if (tableWidget != nullptr)
	{
		tableWidget->insertRow(currentRowCount);
	}

	for (int i = 0; i < argc; ++i)
	{
		QTableWidgetItem* newItem = new QTableWidgetItem(argv[i]);
		if (tableWidget != nullptr)
		{
			tableWidget->setItem(currentRowCount, i, newItem);
		}
	}
}

//用于设置整体界面的样式和字体
void CShowResults::applyStyles()
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