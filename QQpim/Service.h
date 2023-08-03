#ifndef SERVICE_H 
#define SERVICE_H 

//c-->c++-->第三方库--->selflib--->xx.h
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
	CQQPimRequest re; //组合、聚合
};

//1，根据需求抽象实体
//2，分析每个实体属性---》方法
//3, 对象之间的关系
//4, 耦合/解耦


#endif //SERVICE_H
