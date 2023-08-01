#pragma once

#include <cpr/cpr.h>
#include "user.h"
#include"proxy.h"
#include "db.h"

class QyService
{
public:
	// 获取单例对象的接口函数
	static QyService& getInstance();

	void GET_QRCODE_MSG_callback(std::string requesturl);

	void QRCODE_CONFIRM_MSG_callback(std::string msg);

	void START_CRAWL_MSG_callback(std::string msg);

private:
	QyService();

	std::string appid;
	std::string uuid;
	std::string v;
	std::string wx_code;
	std::string t_user_agent;
	std::string SESSION_JSESSIONID;
	std::string __lt;
	std::string __u;
	std::string pim_sid_c;
	std::string nickname;
};

