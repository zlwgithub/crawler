#include"service.h"

// 获取单例对象的接口函数
Service& Service::getInstance()
{
	static Service service;
	return service;
}

Service::Service()
{
	// 初始化proxy
	Proxy::getInstance().set_GET_QRCODE_MSG_ACK_callback(std::bind(&Service::GET_QRCODE_MSG_ACK_callback, this, std::placeholders::_1));
	Proxy::getInstance().set_QRCODE_CONFIRM_MSG_ACK_callback(std::bind(&Service::QRCODE_CONFIRM_MSG_ACK_callback, this, std::placeholders::_1));
	Proxy::getInstance().set_START_CRAWL_MSG_ACK_callback(std::bind(&Service::START_CRAWL_MSG_ACK_callback, this, std::placeholders::_1));
	Proxy::getInstance().set_CURRENT_PROGESS_MSG_ACK_callback(std::bind(&Service::CURRENT_PROGESS_MSG_ACK_callback, this, std::placeholders::_1));
	Proxy::getInstance().initsubpubchannel(1000, 1001);
}

void Service::GET_QRCODE_MSG_ACK_callback(std::string image_path)
{
	emit GET_QRCODE_MSG_ACK_Signal(QString::fromStdString(image_path));
}
void Service::QRCODE_CONFIRM_MSG_ACK_callback(std::string loginres)
{
	emit QRCODE_CONFIRM_MSG_ACK_Signal(QString::fromStdString(loginres));
}
void Service::START_CRAWL_MSG_ACK_callback(std::string image_path)
{
	emit START_CRAWL_MSG_ACK_Signal(QString::fromStdString(image_path));
}
void Service::CURRENT_PROGESS_MSG_ACK_callback(std::string image_path)
{
	emit CURRENT_PROGESS_MSG_ACK_Signal(QString::fromStdString(image_path));
}

//void Service::QRCODE_CONFIRM_MSG_ACK_callback(std::string msg)
//{
//	if (msg == "true")
//	{
//		LOG_INFO("登陆成功!");
//		std::cout << "输入y开始爬取数据:" << std::endl;
//		string cur;
//		getline(cin, cur);
//		if (cur == "y")
//		{
//			string requeststr = "";
//			Proxy::getInstance().send(MsgType::START_CRAWL_MSG, requeststr);
//		}
//	}
//	else
//	{
//		LOG_INFO("登陆失败!");
//	}
//}
//
//void Service::START_CRAWL_MSG_ACK_callback(std::string msg)
//{
//	if (msg.size())
//	{
//		SqlRes sqlres;
//		LOG_INFO("爬取完成，开始读取本地数据库的数据并显示!");
//		sqliteDb sqlitedb;
//		string nickname_db = dbPath + msg + ".db";
//		sqlres = sqlitedb.InitDB(nickname_db.c_str(), false);
//
//		if (sqlres.errnum == 0)
//		{
//			LOG_INFO("打开数据库成功");
//		}
//		else
//		{
//			LOG_ERROR("打开数据库失败");
//		}
//
//		sqlitedb.setDQLCallBack(callback);
//		string sql = "select * from contacts;";
//		sqlitedb.do_sql(sql.c_str());
//		sqlitedb.close();
//	}
//	else
//	{
//		LOG_INFO("查询数据库失败!");
//	}
//}
//
//void Service::CURRENT_PROGESS_MSG_ACK_callback(std::string msg)
//{
//	//显示进度条
//
//}

