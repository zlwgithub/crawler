#pragma once

#include <cpr/cpr.h>
#include "user.h"
#include"proxy.h"
#include "db.h"
#include <variant>

struct QQSynchronizedAssistant_qq {

};

struct QQSynchronizedAssistant_wx {

};

class CrawlService
{
public:
	using cookie = std::string;
	using datastructure = std::variant<double, int>;


	// std::variant<double, int> value = 119;

	if (1 == value.index())
		std::cout << "The value is: " << std::get<1>(value) << std::endl;

	// 获取单例对象的接口函数
	static CrawlService& getInstance();

	/*void getappid(std::string& buf);

	void gett_user_agent(std::string& buf);

	void getv(std::string& buf);

	void getuuid(std::string& buf);

	void getwx_code(std::string& buf);

	void getpim_sid_c(std::string& buf);


	std::string getQRocde(std::string& reqstr);

	std::string getLoginResponse(std::string& reqstr);

	std::string startCrawl(std::string& reqstr);


	void GET_QRCODE_MSG_callback(std::string requesturl);

	void QRCODE_CONFIRM_MSG_callback(std::string msg);*/

	void START_CRAWL_MSG_callback(std::string msg);

private:
	CrawlService();

	unordered_map<cookie, >

		//std::string appid;
		//std::string uuid;
		//std::string v;
		//std::string wx_code;
		//std::string t_user_agent;
		//std::string SESSION_JSESSIONID;
		//std::string __lt;
		//std::string __u;
		//std::string pim_sid_c;
		//std::string nickname;
};

