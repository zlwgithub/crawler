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


//��ȡ��ά�벢���汾�أ����ر��ر���·��
void Service::GET_QRCODE_MSG_callback()
{
	//qq��ά�������ά��һ�ζ�ά��ͻ��һ��,
	// ������ҳurlֻ������һ�β�����ͼƬ������
	cout << "�յ������ά����Ϣ����ʼ�����ά������" << endl;
	string imageUrl = re.fetchQQloginCode();  //·���̶�Ϊ"./code.png";
}

//��ά��ȷ��֮����Ϣ����
void Service::QRCODE_CONFRIM_MSG_callback()
{
	cout << "�յ��û����ȷ����Ϣ����ʼ��ѯ��¼״̬" << endl;
	re.waitScan();
	re.auth();
	bool LoginResponse = re.auth2();  //trueΪ��¼�ɹ���false��¼ʧ��
	
}

void Service::START_CRAWL_CONTACT_MSG_callback()
{
	cout << "�յ���ȡ��ϵ������" << endl;
	string dbname = re.qqContact();  //dbname = ContactDataBase

}

void Service::START_CRAWL_callLog_MSG_callback()
{
	cout << "�յ���ȡͨ����¼����" << endl;
	string dbname = re.callLog(1); //dbname = ContactDataBase
}







