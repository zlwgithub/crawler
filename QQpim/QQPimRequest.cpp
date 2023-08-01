#include "QQPimRequest.h"
#include <iostream>
#include "utils.h"
#include <QTextCodec>
#include<QDebug>
#include <QImage>
#include<string>
#include<urlmon.h>
#include <tchar.h>
#include<regex>
#include<QFILE>
#include < QJsonObject > // { }
#include < QJsonArray > // [ ]
#include < QJsonDocument > // 解析Json
#include < QJsonValue > // int float double bool null { } [ ]
#include < QJsonParseError >
#include "dealData.h"

#pragma comment(lib, "urlmon.lib")
using namespace std;
CQQPimRequest::CQQPimRequest()
{

}

CQQPimRequest::~CQQPimRequest()
{

}

string getGTK(string skey) {
	int hash = 5381;
	for (int i = 0; i < skey.length(); i++) {
		hash += (hash << 5) + skey[i];
	}
	return to_string(hash & 0x7fffffff);
}
string hash33(string qrsig) {
	int e = 0;
	for (int i = 0; i < qrsig.length(); i++) {
		e += (e << 5) + qrsig[i];
	}
	return to_string(e & 2147483647);
}



string CQQPimRequest::fetchLoginJspParam()
{
	setlocale(LC_ALL, "en_US.UTF-8");
	cpr::Header header
	{
		{"Host", "ic.qq.com"},
		{"Connection", "keep-alive"},
		{"Cache-Control", "max-age=0"},
		{"sec-ch-ua", R"("Not.A/Brand";v="8", "Chromium";v="114", "Microsoft Edge";v="114")"},
		{"sec-ch-ua-mobile", "?0"},
		{"sec-ch-ua-platform", R"(Windows)"},
		{"Upgrade-Insecure-Requests", "1"},
		{"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36 Edg/114.0.1823.55"},
		{"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*"},
		{"Upgrade-Insecure-Requests", "1"},
		//{"Accept-Encoding",": gzip, deflate, br"}
	};

	string strUrl = "https://ic.qq.com/pim/login.jsp";

	string strBody = "";

	cpr::Body body{ strBody };
	cpr::Url url{ strUrl };

	m_session.SetUrl(url);
	m_session.SetHeader(header);
	m_session.SetBody(body);
	m_session.SetTimeout(INT_TIMEOUT);
	m_session.SetVerifySsl(false);
	auto request = m_session.Get();
	//utils ut;
	//string output = ut.string_To_UTF8(request.text.c_str());

	//utf-8
	std::cout << request.text.c_str() << std::endl;

	/*QTextCodec* utf8 = QTextCodec::codecForName("utf-8");
	QByteArray encoded = utf8->fromUnicode(QString::fromUtf8(request.text.c_str())).toPercentEncoding();*/
	//QString qstr = QString::fromStdString(request.text);


	//std::cout << qstr.toUtf8() << std::endl;
	//qDebug() << qstr.toUtf8();



	return request.text;
}

string CQQPimRequest::fetchQQloginCode()
{
	
	cpr::Header header
	{
		{"Host", "ssl.ptlogin2.qq.com"},
		{"Connection", "keep-alive"},
		{"sec-ch-ua", R"("Not.A/Brand";v="8", "Chromium";v="114", "Microsoft Edge";v="114")"},
		{"sec-ch-ua-mobile", "?0"},
		{"sec-ch-ua-platform", R"(Windows)"},
		{"Accept", R"(text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7)"},
		{"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36 Edg/114.0.1823.55"},
		
	};

	string strUrl = "https://ssl.ptlogin2.qq.com/ptqrshow?appid=716027609&e=2&l=M&s=3&d=72&v=4&t=0.9013098192986235&daid=383&pt_3rd_aid=101479515&u1=https%3A%2F%2Fgraph.qq.com%2Foauth2.0%2Flogin_jump";

	string strBody = "";

	cpr::Body body{ strBody };
	cpr::Url url{ strUrl };

	m_session.SetUrl(url);
	m_session.SetHeader(header);
	m_session.SetBody(body);
	m_session.SetTimeout(INT_TIMEOUT);
	m_session.SetVerifySsl(false);
	auto request = m_session.Get();
	std::cout << request.text.c_str() << std::endl;
	cout << request.cookies["qrsig"] << endl;
	qrsig = request.cookies["qrsig"];
	//QString imgStr = QString::fromStdString(request.text);
	cout << qrsig << endl;

	//string类型的二维码==>Qimage类型
	QByteArray imgData(request.text.c_str(), request.text.length());
	//QByteArray imgData = QByteArray::fromBase64(imgStr.toUtf8());//字符串转图像数据
	QImage image;
	image.loadFromData(imgData);

	//保存图片
	if (image.save("code.png")) {
		std::cout << "二维码保存成功" << std::endl;
	}
	else {
		std::cout << "二维码保存失败" << std::endl;
	}
	image.save("code.png");
	std::cout << "1" << std::endl;

	

	return request.text;
}

string CQQPimRequest::waitScan()
{
	cout << "waitScan" << endl;
	setlocale(LC_ALL, "en_US.UTF-8");
	cpr::Header header{
		{"Host", "ssl.ptlogin2.qq.com"},
		{"Connection", "keep-alive"},
		{"sec-ch-ua", R"("Not.A/Brand";v="8", "Chromium";v="114", "Microsoft Edge";v="114")"},
		{"sec-ch-ua-mobile", "?0"},
		{"sec-ch-ua-platform", R"(Windows)"},
		{"Accept", R"(text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7)"},
		{"Cookie","qrsig="+qrsig }
	};
	
	//hash 33，解密ptqrtoken
	ptqrtoken = hash33(qrsig);
	/*int e = 0;
	for (int i = 0; i < qrsig.length(); i++) {
		e += (e << 5) + qrsig[i];
	}
	ptqrtoken = to_string(e & 2147483647);*/

	cout << ptqrtoken << endl;

	string url1 = "https://ssl.ptlogin2.qq.com/ptqrlogin?u1=https%3A%2F%2Fgraph.qq.com%2Foauth2.0%2Flogin_jump&ptqrtoken=" + ptqrtoken + "&ptredirect=0&h=1&t=1&g=1&from_ui=1&ptlang=2052&action=0-0-1690078835484&js_ver=23071715&js_type=1&login_sig=unOqtFPXr5E7FLzPuWQ4jIeedJJZ-TKojigtyaUu0uoy948lzfEgrzNIOm-iwBkF&pt_uistyle=40&aid=716027609&daid=383&pt_3rd_aid=101479515&has_onekey=1&&o1vId=cb57389526a48aa9f1b565b2a0b91b6d&pt_js_version=v1.46.0";
	cpr::Url url{
		url1
	};

	cpr::Body body{

	};

	m_session.SetUrl(url);
	m_session.SetHeader(header);
	m_session.SetBody(body);
	m_session.SetTimeout(INT_TIMEOUT);
	//m_session.SetVerifySsl(false);
	auto request = m_session.Get();
	cout << request.url << endl;
	//cout << request.text.c_str() << endl;
	auto str1 = request.text.c_str();

	std::regex reg("'(.*)','(.*)','(.*)','(.*)'");
	std::cmatch m;
	auto ret = std::regex_search(str1, m, reg);
	authUrl = m[2];
	/*if (ret)
	{
		for (auto& elem : m)
			std::cout << elem << std::endl;
	}*/

	/*std::cout << "prefix:" << m.prefix() << std::endl;
	std::cout << "suffix:" << m.suffix() << std::endl;*/


	return request.text;
	
}

string CQQPimRequest::auth()
{
	cout << "auth" << endl;
	setlocale(LC_ALL, "en_US.UTF-8");
	cpr::Header header{
		{"Host", "ssl.ptlogin2.graph.qq.com"},
		{"Connection", "keep-alive"},
		{"sec-ch-ua", R"("Not.A/Brand";v="8", "Chromium";v="114", "Microsoft Edge";v="114")"},
		{"sec-ch-ua-mobile", "?0"},
		{"sec-ch-ua-platform", R"(Windows)"},
		{"Accept", R"(text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7)"},
	};
	
	cpr::Url url{
		authUrl
	};

	cpr::Body body{

	};

	m_session.SetUrl(url);
	m_session.SetHeader(header);
	m_session.SetBody(body);
	m_session.SetTimeout(INT_TIMEOUT);
	m_session.SetVerifySsl(false);
	auto request = m_session.Get();
	cout << request.url << endl;
	//cout << request.text.c_str() << endl;
	cout << request.cookies["p_uin"] << endl;
	cout << request.cookies["pt4_token"] << endl;
	cout << request.cookies["p_skey"] << endl;
	cout << request.cookies["pt_oauth_token"] << endl;
	p_uin = request.cookies["p_uin"];
	pt4_token = request.cookies["pt4_token"];
	p_skey = request.cookies["p_skey"];
	pt_oauth_token = request.cookies["pt_oauth_token"];
	g_tk = getGTK(p_skey);
	cout <<"g_tk:" << g_tk << endl;

	return request.text;
}

string CQQPimRequest::auth2()
{
	cout << "auth2" << endl;
	setlocale(LC_ALL, "en_US.UTF-8");
	cpr::Header header{
		{"Host", "graph.qq.com"},
		{"Connection", "keep-alive"},
		{"sec-ch-ua", R"("Not.A/Brand";v="8", "Chromium";v="114", "Microsoft Edge";v="114")"},
		{"sec-ch-ua-mobile", "?0"},
		{"sec-ch-ua-platform", R"(Windows)"},
		{"Accept", R"(text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7)"},
		{"Cookie","p_uin=" + p_uin + "; pt4_token=" + pt4_token + "; p_skey=" + p_skey + "; pt_oauth_token=" + pt_oauth_token+"; pt_login_type=3"}
	};

	cpr::Url url{
		"https://graph.qq.com/oauth2.0/authorize"
	};

	cpr::Body body{
		"response_type=code&client_id=101479515&redirect_uri=https%3A%2F%2Fic.qq.com%2Fcommon%2Fconnectqq.jsp&scope=get_user_info&state=STATE&switch=&from_ptlogin=1&src=1&update_auth=1&openapi=1010&g_tk="+g_tk+"&auth_time=1690160280448&ui=16A9CCE8-79A9-4D11-B12E-B827BD7BA976"
	};

	m_session.SetUrl(url);
	m_session.SetHeader(header);
	m_session.SetBody(body);
	m_session.SetTimeout(INT_TIMEOUT);
	m_session.SetVerifySsl(false);
	auto request = m_session.Post();
	cout << request.url << endl;
	//cout << request.text.c_str() << endl;
	cout << "SESSION_JSESSIONID" << request.cookies["SESSION_JSESSIONID"] << endl;
	cout << "__lt" << request.cookies["__lt"] << endl;
	cout << "__u" << request.cookies["__u"] << endl;
	SESSION_JSESSIONID = request.cookies["SESSION_JSESSIONID"];
	__lt = request.cookies["__lt"];
	__u = request.cookies["__u"];




	return string();
}




string CQQPimRequest::qqContact()
{
	cout << "qqContact" << endl;
	setlocale(LC_ALL, "en_US.UTF-8");
	cpr::Header header{
		{"Host", "ic.qq.com"},
		{"Connection", "keep-alive"},
		{"sec-ch-ua", R"("Not.A/Brand";v="8", "Chromium";v="114", "Microsoft Edge";v="114")"},
		{"sec-ch-ua-mobile", "?0"},
		{"sec-ch-ua-platform", R"(Windows)"},
		{"Accept", R"(text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7)"},
		{"Cookie","SESSION_JSESSIONID=" + SESSION_JSESSIONID + "; __lt=" + __lt + "; __u=" + __u}
	};

	cpr::Url url{
		"https://ic.qq.com/pim/contact.jsp"
	};

	cpr::Body body{

	};

	m_session.SetUrl(url);
	m_session.SetHeader(header);
	m_session.SetBody(body);
	m_session.SetTimeout(INT_TIMEOUT);
	m_session.SetVerifySsl(false);
	auto request = m_session.Get();
	//cout << request.text.c_str() << endl;
	string result = request.text.c_str();
	int start = result.find("contacts:");
	int end = result.find("cesu:");
	data1 = result.substr(start + 10, end - start - 13);
	/*cout << data1 << endl;
	QFile writeFile("./contact.txt");
	writeFile.open(QIODevice::WriteOnly);
	writeFile.write(data1.c_str());
	writeFile.close();*/

	dealData deal;
	deal.dealJsonStringContact(data1.c_str());

	return string();

}

string CQQPimRequest::callLog(int id)
{
	
	cout << "CallLog" << endl;
	setlocale(LC_ALL, "en_US.UTF-8");
	cpr::Header header{
		{"Host", "ic.qq.com"},
		{"Connection", "keep-alive"},
		{"Content-Length","95"},
		{"sec-ch-ua", R"("Not/A)Brand";v="99", "Microsoft Edge";v="115", "Chromium";v="115")"},
		{"Accept", R"(application/json, text/javascript, */*; q=0.01)"},
		{"Content-Type","application/x-www-form-urlencoded; charset=UTF-8"},
		{"User-Agent","Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36 Edg/115.0.1901.183"},
		{"sec-ch-ua-mobile", "?0"},
		{"sec-ch-ua-platform", R"(Windows)"},	
		{"Cookie","SESSION_JSESSIONID=" + SESSION_JSESSIONID + "; __lt=" + __lt + "; __u=" + __u}
	};

	cpr::Url url{
		"https://ic.qq.com/pim/callog/searchbykey_json.jsp"
	};

	cpr::Body body{
		"myuinmd5=d7c0b7c59a04123db36780ee3e25150f&X_Content_Type=json&calltype=all&pageNo="+std::to_string(id)+"&pageSize=50"
	};

	m_session.SetUrl(url);
	m_session.SetHeader(header);
	m_session.SetBody(body);
	m_session.SetTimeout(INT_TIMEOUT);
	m_session.SetVerifySsl(false);
	auto request = m_session.Post();
	//cout << request.text.c_str() << endl;
	string result = request.text.c_str();
	if (id == 1) {
		//解析为Json文档
		QJsonParseError json_error;
		QJsonDocument json_doc = QJsonDocument::fromJson(request.text.c_str(), &json_error);

		//是否正常解析Json数据
		if (json_doc.isNull() || json_doc.isEmpty() || json_error.error != QJsonParseError::NoError)
			return NULL;

		//解析文档中的Object
		const QJsonObject json_obj = json_doc.object();
		QJsonValue root = json_obj.value("info");
		QJsonObject info = root.toObject();

		QJsonValue pageCount = info.value("pageCount");
		qDebug() << "pagecount" << pageCount.toInt();
		pages = pageCount.toInt();
	}
	
	/*int start = result.find("contacts:");
	int end = result.find("cesu:");
	data1 = result.substr(start + 10, end - start - 13);
	cout << data1 << endl;
	QFile writeFile("./contact.txt");
	writeFile.open(QIODevice::WriteOnly);
	writeFile.write(data1.c_str());
	writeFile.close();*/

	/*string filepath = "./tel" + std::to_string(id) + ".txt";

	QFile writeFile(filepath.c_str());
	writeFile.open(QIODevice::WriteOnly);
	writeFile.write(result.c_str());
	writeFile.close();*/
	dealData deal;
	deal.dealJsonStringTel(result.c_str());

	
	if (pages > 1) {
		pages--;
		callLog(++id);
		
	}
	

	return string();
}



string CQQPimRequest::fetchQrcode()
{
	setlocale(LC_ALL, "en_US.UTF-8");
	cpr::Header header{
		{"Host", "open.weixin.qq.com"},
		{"Connection", "keep-alive"},
		{"sec-ch-ua", R"("Not.A/Brand";v="8", "Chromium";v="114", "Microsoft Edge";v="114")"},
		{"sec-ch-ua-mobile", "?0"},
		{"sec-ch-ua-platform", R"(Windows)"},
		{"Accept", R"(text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7)"},
	};

	cpr::Url url{
		"https://open.weixin.qq.com/connect/qrconnect?appid=wx6cf625a6815044fa&redirect_uri=https://ic.qq.com/common/connectwx.jsp&response_type=code&state=STATE&href=https://y.gtimg.cn/mediastyle/yqq/popup_wechat.css&scope=snsapi_login"
	};

	cpr::Body body{

	};

	m_session.SetUrl(url);
	m_session.SetHeader(header);
	m_session.SetBody(body);
	m_session.SetTimeout(INT_TIMEOUT);
	m_session.SetVerifySsl(false);
	auto request = m_session.Get();
	//cout << request.text.c_str() << endl;
	string result = request.text.c_str();
	int index = result.find("qrcode/");
	string substr = result.substr(index + 7, 16);
	cout << substr << endl;
		

	return substr;
}

string CQQPimRequest::fetchQrConnect()
{

	//setlocale(LC_ALL, "en_US.UTF-8");
	cpr::Header header{
		{"Host", "lp.open.weixin.qq.com"},
		{"Connection", "keep-alive"},
		{"sec-ch-ua", R"("Not.A/Brand";v="8", "Chromium";v="114", "Microsoft Edge";v="114")"},
		{"sec-ch-ua-mobile", "?0"},
		{"sec-ch-ua-platform", R"(Windows)"},
		{"Accept", R"(text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7)"},
	};

	string url1 = "https://lp.open.weixin.qq.com/connect/l/qrconnect?uuid="+substr+"&_=1689912876322";
	cout << url1 << endl;
	cpr::Url url{
		url1
	};

	cpr::Body body{

	};

	m_session.SetUrl(url);
	m_session.SetHeader(header);
	m_session.SetBody(body);
	m_session.SetTimeout(INT_TIMEOUT);
	m_session.SetVerifySsl(false);
	auto request = m_session.Get();
	
	cout << "qrconnect" << endl;
	string result = request.text.c_str();
	cout << result << endl;

	int index = result.find("wx_code");
	wxCode = result.substr(index + 9, 32);
	cout << wxCode << endl;
	return result;
}

string CQQPimRequest::confirmLogin()
{
	cout << "confirmLogin" << endl;
	cpr::Header header{
		{"Host", "ic.qq.com"},
		{"Connection", "keep-alive"},
		{"sec-ch-ua", R"("Not.A/Brand";v="8", "Chromium";v="114", "Microsoft Edge";v="114")"},
		{"sec-ch-ua-mobile", "?0"},
		{"sec-ch-ua-platform", R"(Windows)"},
		//{"Referer","https://open.weixin.qq.com/"},
		{"Accept", R"(text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7)"},
	};

	string url1 = "https://ic.qq.com/common/connectwx.jsp?code=" + wxCode + "&state=STATE";
	cout << url1 << endl;
	cpr::Url url{
		url1
	};

	cpr::Body body{

	};

	m_session.SetUrl(url);
	m_session.SetHeader(header);
	m_session.SetBody(body);
	m_session.SetTimeout(INT_TIMEOUT);
	m_session.SetVerifySsl(false);
	auto request = m_session.Get();
	cout << request.text.c_str() << endl;
	
	return string();
}

string CQQPimRequest::contact()
{
	cout << "contact" << endl;
	cpr::Header header{
		{"Host", "ic.qq.com"},
		{"Connection", "keep-alive"},
		{"sec-ch-ua", R"("Not.A/Brand";v="8", "Chromium";v="114", "Microsoft Edge";v="114")"},
		{"sec-ch-ua-mobile", "?0"},
		{"sec-ch-ua-platform", R"(Windows)"},
		//{"Referer","https://open.weixin.qq.com/"},
		{"Accept", R"(text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7)"},
	};

	string url1 = "https://ic.qq.com/pim/contact.jsp";
	cout << url1 << endl;
	cpr::Url url{
		url1
	};

	cpr::Body body{

	};

	m_session.SetUrl(url);
	m_session.SetHeader(header);
	m_session.SetBody(body);
	m_session.SetTimeout(INT_TIMEOUT);
	m_session.SetVerifySsl(false);
	auto request = m_session.Get();
	//cout << request.text.c_str() << endl;
	string result = request.text.c_str();
	int start = result.find("contacts:");
	int end = result.find("cesu:");
	data1 = result.substr(start + 10, end - start-13);
	cout << data1 << endl;
	return string();
}



bool CQQPimRequest::fetchWXloginCode()
{

	
	substr = fetchQrcode();
	string strUrl = "https://open.weixin.qq.com/connect/qrcode/"+substr;
	cout << strUrl << endl;
	
	size_t len = strUrl.length();//获取字符串长度
	int nmlen = MultiByteToWideChar(CP_ACP, 0, strUrl.c_str(), len + 1, NULL, 0);//如果函数运行成功，并且cchWideChar为零，
	//返回值是接收到待转换字符串的缓冲区所需求的宽字符数大小。
	wchar_t* buffer = new wchar_t[nmlen];
	MultiByteToWideChar(CP_ACP, 0, strUrl.c_str(), len + 1, buffer, nmlen);
	HRESULT hr = URLDownloadToFile(NULL, buffer, _T(".//code.jpg"), 0, NULL);
	if (hr == S_OK)
	{
		cout << "ok" << endl;
	}

	return 0;
}

//htmlcpp