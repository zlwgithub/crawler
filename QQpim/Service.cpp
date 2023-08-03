#include "Service.h"
#include <iostream>
#include <string>
//using namespace std;


//string getQrCode() {
//	string imagesPath = re.fetchQQloginCode();
//	return imagesPath;
//}
//
//bool getLoginStatus() {
//	re.waitScan();
//	re.auth();
//	bool result = re.auth2();
//	return result;
//}
//
//string getContact() {
//	re.qqContact();
//	return "contact";
//}
//
//string getCallLog() {
//	re.callLog(1);
//	return "callLog";
//}


Service::Service()
{
}

Service::~Service()
{
}


//获取二维码并保存本地，返回本地保存路径
void Service::GET_QRCODE_MSG_callback()
{
	//qq二维码请求二维码一次二维码就会变一次,
	// 所以网页url只能请求一次并保存图片到本地
	cout << "收到请求二维码消息，开始请求二维码数据" << endl;
	string imageUrl = re.fetchQQloginCode();  //路径固定为"./code.png";
}

//二维码确认之后信息返回
void Service::QRCODE_CONFRIM_MSG_callback()
{
	cout << "收到用户点击确认消息，开始查询登录状态" << endl;
	re.waitScan();
	re.auth();
	bool LoginResponse = re.auth2();  //true为登录成功，false登录失败
	
}

void Service::START_CRAWL_CONTACT_MSG_callback()
{
	cout << "收到爬取联系人请求" << endl;
	string dbname = re.qqContact();  //dbname = ContactDataBase

}

void Service::START_CRAWL_callLog_MSG_callback()
{
	cout << "收到爬取通话记录请求" << endl;
	string dbname = re.callLog(1); //dbname = ContactDataBase
}







