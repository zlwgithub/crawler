#ifndef QQPIMREQUEST_H
#define QQPIMREQUEST_H



#include <string>
#include <cpr/session.h>

using std::string;
using namespace cpr;

#define INT_TIMEOUT 3000

class CQQPimRequest
{
public:
	CQQPimRequest();
	~CQQPimRequest();

public:
	string fetchLoginJspParam();

	
	//wx����
	bool fetchWXloginCode();

	string fetchQrcode();

	string fetchQrConnect();

	string confirmLogin();

	string contact();

	string callLog(int id);

	//qq����
	string fetchQQloginCode();

	bool waitScan();

	string auth();

	bool auth2();

	string qqContact();

	
	

private:
	Session m_session;
	string substr;
	string wxCode;
	//��ϵ������
	string data1;
	//��������
	string data2;

	string qrsig;

	string  ptqrtoken;

	string authUrl;

	string p_uin;
	string pt4_token;
	string p_skey;
	string pt_oauth_token;
	string g_tk;
	string SESSION_JSESSIONID;
	string __lt;
	string __u;
	int pages;
};

#endif // !QQPIMREQUEST_H