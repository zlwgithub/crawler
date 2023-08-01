#include"service.h"
#include<iostream>
using namespace std;


// 获取单例对象的接口函数
CrawlService& CrawlService::getInstance()
{
	static CrawlService service;
	return service;
}

CrawlService::CrawlService()
{
	Proxy::getInstance().set_GET_QRCODE_MSG_callback(std::bind(&CrawlService::GET_QRCODE_MSG_callback, this, std::placeholders::_1));
	Proxy::getInstance().set_QRCODE_CONFIRM_MSG_callback(std::bind(&CrawlService::QRCODE_CONFIRM_MSG_callback, this, std::placeholders::_1));
	Proxy::getInstance().set_START_CRAWL_MSG_callback(std::bind(&CrawlService::START_CRAWL_MSG_callback, this, std::placeholders::_1));
	Proxy::getInstance().initsubpubchannel(1001, 1000);
}

void CrawlService::getappid(std::string& buf)
{
	auto it1 = buf.find("appid=");
	auto it2 = buf.find("=", it1);
	auto it3 = buf.find("&", it2);
	appid =  buf.substr(it2 + 1, it3 - it2 - 1);
}

void CrawlService::gett_user_agent(std::string& buf)
{
	auto it1 = buf.find("t_user_agent=");
	auto it2 = buf.find("=", it1);
	auto it3 = buf.find("&", it2);
	t_user_agent =  buf.substr(it2 + 1, it3 - it2 - 1);
}

void CrawlService::getv(std::string& buf)
{
	auto it1 = buf.find("/pim/loginbox.html?v=");
	auto it2 = buf.find("=", it1);
	auto it3 = buf.find("\"", it2);
	v =  buf.substr(it2 + 1, it3 - it2 - 1);
}

void CrawlService::getuuid(std::string& buf)
{
	auto it1 = buf.find("uuid=");
	auto it2 = buf.find("=", it1);
	auto it3 = buf.find("\"", it2);
	uuid =  buf.substr(it2 + 1, it3 - it2 - 1);
}

void CrawlService::getwx_code(std::string& buf)
{
	auto it1 = buf.find("window.wx_code='");
	auto it2 = buf.find("'", it1);
	auto it3 = buf.find("'", it2 + 1);
	wx_code =  buf.substr(it2 + 1, it3 - it2 - 1);
}

void CrawlService::getpim_sid_c(std::string& buf)
{
	auto it1 = buf.find("pim_sid_c");
	auto it2 = buf.find("'", it1);
	auto it3 = buf.find("'", it2 + 1);
	pim_sid_c =  buf.substr(it2 + 1, it3 - it2 - 1);
}

std::string CrawlService::getQRocde(std::string& reqstr)
{
	std::string destUrl = reqstr;
	const cpr::Response& responseForGet1 = cpr::Get(cpr::Url(destUrl));
	std::string buf = responseForGet1.text;
	getappid(buf);
	getv(buf);
	auto& cookies = responseForGet1.cookies;
	for (auto a = cookies.begin(); a != cookies.end(); ++a)
	{
		if (a->GetName() == "t_user_agent")
		{
			t_user_agent = a->GetValue();
		}
	}

	std::string str1 = "https://open.weixin.qq.com/connect/qrconnect?appid=";
	std::string str2 = "&redirect_uri=https://ic.qq.com/common/connectwx.jsp&response_type=code&state=STATE&href=https://y.gtimg.cn/mediastyle/yqq/popup_wechat.css&scope=snsapi_login";
	std::string newstr = str1 + appid + str2;
	const cpr::Response& responseForGet2 = cpr::Get(cpr::Url(newstr));
	buf = responseForGet2.text;
	getuuid(buf);

	newstr = "https://open.weixin.qq.com/connect/qrcode/";
	newstr += uuid;
	const cpr::Response& responseForGet3 = cpr::Get(cpr::Url(newstr));
	buf = responseForGet3.text;
	// 字节流转png图片
	std::string image_path = QRcodePath + "QRcode1.png";
	writeintfile(image_path, buf, true, true);
	return image_path;
}

std::string CrawlService::getLoginResponse(std::string& reqstr)
{
	std::string newstr = "https://lp.open.weixin.qq.com/connect/l/qrconnect?uuid=";
	newstr += uuid;
	newstr += "&_=";
	newstr += v;
	const cpr::Response& responseForGet = cpr::Get(cpr::Url(newstr));
	std::string buf = responseForGet.text;
	getwx_code(buf);
	if (wx_code.size() > 0)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}

std::string CrawlService::startCrawl(std::string& reqstr)
{
	cpr::Session session;
	std::string requrl1 = "https://ic.qq.com/common/connectwx.jsp?code=" + wx_code + "&state=STATE";
	session.SetUrl(requrl1);

	const cpr::Response& responseForGet1 = session.Get();
	auto& responsecookies1 = responseForGet1.cookies;
	for (auto a = responsecookies1.begin(); a != responsecookies1.end(); ++a)
	{
		if (a->GetName() == "SESSION_JSESSIONID")
		{
			SESSION_JSESSIONID = a->GetValue();
		}
		if (a->GetName() == "__lt")
		{
			__lt = a->GetValue();
		}
		if (a->GetName() == "__u")
		{
			__u = a->GetValue();
		}
	}

	std::string destUrl = "https://ic.qq.com/pim/contact.jsp";

	std::string cookie1 = "t_user_agent=" + t_user_agent + ";";
	std::string cookie2 = "loginIntroImg=1;";
	std::string cookie3 = "SESSION_JSESSIONID=" + SESSION_JSESSIONID + ";";
	std::string cookie4 = "__lt=" + __lt + ";";
	std::string cookie5 = "__u=" + __u;
	std::string cookies = cookie1 + cookie2 + cookie3 + cookie4 + cookie5;

	const cpr::Response& responseForGet2 = cpr::Get(cpr::Url(destUrl), cpr::Header{ {"Host", "ic.qq.com"},
																				   {"Connection", "keep-alive"},
																				   {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36"},
																				   {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"},
																				   {"Cookie", cookies} });
	std::string buf = responseForGet2.text;
	// 解析pim_sid_c
	getpim_sid_c(buf);

	// 解析json联系人数据， contacts: cesu
	auto it1 = buf.find("contacts:");
	auto it2 = buf.find("cesu");
	auto it3 = buf.find("{", it1);
	std::string subbuf = buf.substr(it3, it2 - it3 - 3);
	json js = json::parse(subbuf);
	auto objs = js["vacrds"];
	vector<User> vec;
	for (auto obj : objs)
	{

		User user;
		if (!obj["vcard"]["N"][0]["VALUE"].is_null())
		{
			std::string temp = obj["vcard"]["N"][0]["VALUE"];
			user.setNAME(temp.substr(0, temp.size() - 4));
		}
		if (!obj["vcard"]["BDAY"][0]["VALUE"].is_null())
		{
			user.setBDAY(obj["vcard"]["BDAY"][0]["VALUE"]);
		}
		if (!obj["vcard"]["NOTE"][0]["VALUE"].is_null())
		{
			user.setNOTE(obj["vcard"]["NOTE"][0]["VALUE"]);
		}
		if (!obj["vcard"]["QQ"][0]["VALUE"].is_null())
		{
			user.setQQ(obj["vcard"]["QQ"][0]["VALUE"]);
		}
		if (!obj["vcard"]["TITLE"][0]["VALUE"].is_null())
		{
			user.setTITLE(obj["vcard"]["TITLE"][0]["VALUE"]);
		}
		if (!obj["vcard"]["TEL"][0]["VALUE"].is_null())
		{
			user.setTEL(obj["vcard"]["TEL"][0]["VALUE"]);
		}
		if (!obj["vcard"]["EMAIL"][0]["VALUE"].is_null())
		{
			user.setEMAIL(obj["vcard"]["EMAIL"][0]["VALUE"]);
		}
		if (!obj["vcard"]["ORG"][0]["VALUE"].is_null())
		{
			std::string temp = obj["vcard"]["ORG"][0]["VALUE"];
			user.setORG(temp.substr(0, temp.size() - 1));
		}
		vec.push_back(user);
	}

	// 获取当前用户信息
	json jspim_sid_c;
	jspim_sid_c["req"]["pimsid"] = pim_sid_c;
	std::string jspim_sid_c_str = jspim_sid_c.dump();
	std::string url = "https://jsonproxy.3g.qq.com/forward?cmdid=1871";
	const cpr::Response& responseForGet3 = cpr::Post(cpr::Url(url), cpr::Header{ {"Host", "jsonproxy.3g.qq.com"}, {"Connection", "keep-alive"}, {"Content-Length", to_string(jspim_sid_c_str.size())}, {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36"}, {"Content-Type", "text/plain"}, {"Origin", "https://ic.qq.com"}, {"Referer", "https://ic.qq.com/"}, {"Accept", "application/json, text/javascript, */*; q=0.01"}, {"Accept-Encoding", "gzip, deflate, br"}, {"Accept-Language", "zh-CN,zh;q=0.9"} }, cpr::Body{ jspim_sid_c_str });
	json jsuserinfo = json::parse(responseForGet3.text);
	nickname = jsuserinfo["data"]["resp"]["nickname"];

	//建立nickname.db文件
	sqliteDb sqlitedb;
	string nickname_db = dbPath + nickname + ".db";
	SqlRes sqlres;
	sqlres = sqlitedb.InitDB(nickname_db.c_str(), true);
	if (sqlres.errnum)
	{
		LOG_ERROR("建立%s.db文件出错", nickname.c_str());
		return "";
	}
	else
	{
		LOG_INFO("建立%s.db文件成功", nickname.c_str());
	}

	////创建contacts表
	std::string create_table_sql = "CREATE TABLE IF NOT EXISTS contacts(NAME VARCHAR(100) PRIMARY KEY, NOTE VARCHAR(100) DEFAULT NULL, BDAY VARCHAR(100)  NOT NULL, QQ VARCHAR(100) DEFAULT NULL, TITLE VARCHAR(100) DEFAULT NULL, TEL VARCHAR(100) DEFAULT NULL, EMAIL VARCHAR(100) DEFAULT NULL, ORG VARCHAR(100) DEFAULT NULL)";
	sqlitedb.do_sql(create_table_sql.c_str(),nullptr);
	if (sqlres.errnum)
	{
		LOG_ERROR("在%s数据库下创建contacts表出错", nickname.c_str());
		return "";
	}
	else
	{
		LOG_INFO("在%s数据库下创建contacts表成功", nickname.c_str());
	}

	//清空contacts表数据
	string flush_table_sql = "delete from contacts where 1;";
	sqlres = sqlitedb.do_sql(flush_table_sql.c_str(),nullptr);
	if (sqlres.errnum)
	{
		LOG_ERROR("在%s数据库下清空contacts表出错", nickname.c_str());
		return "";
	}
	else
	{
		LOG_INFO("在%s数据库下清空contacts表成功", nickname.c_str());
	}

	//插入数据到contacts表
	char insert_sql[4096] = { 0 };
	sprintf(insert_sql, "insert into contacts(NAME,NOTE,BDAY,QQ,TITLE,TEL,EMAIL,ORG) values");
	int vec_size = vec.size();
	for (int i = 0; i < vec_size; ++i)
	{
		User& user = vec[i];
		if (i != 0)
		{
			sprintf(insert_sql + strlen(insert_sql), ",('%s','%s','%s','%s','%s','%s','%s','%s')", user.getNAME().c_str(), user.getNOTE().c_str(), user.getBDAY().c_str(), user.getQQ().c_str(), user.getTITLE().c_str(), user.getTEL().c_str(), user.getEMAIL().c_str(), user.getORG().c_str());
		}
		else
		{
			sprintf(insert_sql + strlen(insert_sql), "('%s','%s','%s','%s','%s','%s','%s','%s')", user.getNAME().c_str(), user.getNOTE().c_str(), user.getBDAY().c_str(), user.getQQ().c_str(), user.getTITLE().c_str(), user.getTEL().c_str(), user.getEMAIL().c_str(), user.getORG().c_str());
		}
	}
	//string m = "90";
	//Proxy::getInstance().send(CURRENT_PROGESS_MSG_ACK, m);
	sqlres = sqlitedb.do_sql(insert_sql,nullptr);
	if (sqlres.errnum)
	{
		LOG_ERROR("在%s数据库下为表contacts添加数据出错", nickname.c_str());
		return "";
	}
	else
	{
		LOG_INFO("在%s数据库下为表contacts添加数据成功", nickname.c_str());
	}
	sqlitedb.close();
	return nickname_db;
}


void CrawlService::GET_QRCODE_MSG_callback(std::string requesturl)
{
	cout << "收到请求二维码消息, 开始请求二维码数据:" << requesturl << endl;
	LOG_INFO("收到请求二维码消息,开始请求二维码数据:%s", requesturl.c_str());
	std::string imagedest = getQRocde(requesturl);
	Proxy::getInstance().send(MsgType::GET_QRCODE_MSG_ACK, imagedest);
}

void CrawlService::QRCODE_CONFIRM_MSG_callback(std::string msg)
{
	cout << "收到用户点击确认消息,开始查询登录状态:"  << endl;
	LOG_INFO("收到用户点击确认消息,开始查询登录状态");
	std::string LoginResponse = getLoginResponse(msg);
	Proxy::getInstance().send(MsgType::QRCODE_CONFIRM_MSG_ACK, LoginResponse);
}

void CrawlService::START_CRAWL_MSG_callback(std::string msg)
{
	cout << "收到START_CRAWL_MSG请求:" << endl;
	LOG_INFO("收到START_CRAWL_MSG请求");
	std::string dbname = startCrawl(msg);
	Proxy::getInstance().send(MsgType::START_CRAWL_MSG_ACK, dbname);
	cout << "回复START_CRAWL_MSG请求:%s" << dbname <<endl;
}