#pragma once

#include "user.h"
#include"proxy.h"
#include "db.h"
#include<iostream>

//处理数据库的查询结果
int callback(void* data, int argc, char** argv, char** azColName);


class Service
{
public:
	// 获取单例对象的接口函数
	static Service& getInstance();

	void GET_QRCODE_MSG_ACK_callback(std::string msg);

	void QRCODE_CONFIRM_MSG_ACK_callback(std::string msg);

	void START_CRAWL_MSG_ACK_callback(std::string msg);

	void CURRENT_PROGESS_MSG_ACK_callback(std::string msg);

private:
	Service();
};