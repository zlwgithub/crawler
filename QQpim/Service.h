#ifndef SERVICE_H 
#define SERVICE_H 

//c-->c++-->��������--->selflib--->xx.h
#include <string>
#include "QQPimRequest.h"

using namespace std;

class Service
{
public:
	Service();
	~Service();

public:
	void GET_QRCODE_MSG_callback();

	void QRCODE_CONFRIM_MSG_callback();

	void START_CRAWL_CONTACT_MSG_callback();

	void START_CRAWL_callLog_MSG_callback();

private:
	CQQPimRequest re; //��ϡ��ۺ�
};

//1�������������ʵ��
//2������ÿ��ʵ������---������
//3, ����֮��Ĺ�ϵ
//4, ���/����


#endif //SERVICE_H
