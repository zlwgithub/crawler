#include "ShowResults.h"
#include <QtWidgets/QApplication>
#include <proxy.h>
#include<string>
#include<vector>

void func(std::string s)
{
	json js = json::parse(s);
	std::vector<std::string> vec = js["contrats"];
	ShowResults w(nullptr, vec);
	//查询数据库
	w.show();
}

int main(int argc, char* argv[])
{
	Proxy::getInstance().set_QRCODE_CONFIRM_MSG_ACK_callback(std::bind(func, std::placeholders::_1));
	Proxy::getInstance().initsubpubchannel(1000, 1001);

	QApplication a(argc, argv);
	std::vector<std::string> vec;
	ShowResults w(nullptr, vec);
	w.show();

	// 假设已经有了要添加的数据，分别存储在变量中
	 //QString 姓名 = "张三";
	 //QString 描述 = "某些描述";
	 //QString 出生日期 = "1990-01-01";
	 //QString 电话 = "123456789";
	 //QString 邮箱 = "zhangsan@example.com";
	 //QString QQ = "12345678";
	 //QString 公司 = "示例公司";
	 //QString 职位 = "软件工程师";

	 //// 调用函数将数据添加到表格中
	 //QTableWidget* tableWidget = w.getTableWidget();
	 //if (!姓名.isEmpty() && !描述.isEmpty() && !出生日期.isEmpty() &&
	 //    !电话.isEmpty() && !邮箱.isEmpty() && !QQ.isEmpty() && !公司.isEmpty() && !职位.isEmpty())
	 //{
	 //    w.addDataToTable(tableWidget, 姓名, 描述, 出生日期, 电话, 邮箱, QQ, 公司, 职位);
	 //}



	return a.exec();
}
