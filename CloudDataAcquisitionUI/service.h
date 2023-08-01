#pragma once

#include "user.h"
#include"proxy.h"
#include "db.h"
#include<iostream>
#include<qthread.h>



class Service :public QThread
{
	Q_OBJECT
public:
	// 获取单例对象的接口函数
	static Service& getInstance();

	void GET_QRCODE_MSG_ACK_callback(std::string msg);

	void QRCODE_CONFIRM_MSG_ACK_callback(std::string msg);

	void START_CRAWL_MSG_ACK_callback(std::string msg);

	void CURRENT_PROGESS_MSG_ACK_callback(std::string msg);

signals:
	void GET_QRCODE_MSG_ACK_Signal(QString qs);
	void QRCODE_CONFIRM_MSG_ACK_Signal(QString qs);
	void START_CRAWL_MSG_ACK_Signal(QString qs);
	void CURRENT_PROGESS_MSG_ACK_Signal(QString qs);

private:
	Service();
};