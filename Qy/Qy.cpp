#include "Qy.h"
#include <iostream>
#include <fstream>
#include <qtextcodec.h>
#include <string>
#include <vector>
#include <pthread.h>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
using namespace cpr;

Qy::Qy()
{

}
Qy::~Qy()
{

}

string _qyeruid;
string _guid;
string PHPSESSID;
string qy_uuid;
string qy_wx_code;
string cdb_auth;
string uID;

string place[22][3] = {
	"中国", "11", "country",
	"韩国", "233", "country",
	"日本", "14", "country",
	"??????", "215", "country",
	"??????????", "62", "city",
	"??????????", "446", "country",
	"??????????", "219", "country",
	"????????????????", "213", "country",
	"??????", "13", "country",
	"????????", "186", "country",
	"??????", "15", "country",
	"??????????", "198", "country",
	"??????????", "189", "country",
	"??????????", "424", "country",
	"??????????", "208", "country",
	"????????????", "182", "country",
	"????????", "244", "country",
	"????????", "236", "country",
	"??????????", "238", "country",
	"ī????????", "515", "country",
	"????????????", "241", "country",
	"??????????????", "240", "country"
};


void saveDataToFile(string path, string msg, bool binary)
{
	auto fcntl = ios::out | ios::trunc;
	if (binary)
	{
		fcntl |= ios::binary;
	}
	ofstream file(path, fcntl);

	if (file && !file.is_open())
	{
		cout << "Error creating" << endl;
	}
	else
	{
		cout << "Success!!!" << endl;
		auto szDecodedLength = msg.size();
		file.write(reinterpret_cast<const char*>(msg.c_str()), szDecodedLength);
		file.close();
	}
}

void get_uuid()
{
	string url = "https://passport.qyer.com/oauth?using=weixin&ref=https://www.qyer.com/";
	Response r2 = Get(Url(url));
	//cout << "------------------------------------------------->>>>>>>>>>>>>>" << endl;
	//cout << r2.text << endl;
	//cout << "------------------------------------------------->>>>>>>>>>>>>>" << endl;

	string text = r2.text;
	int start = text.find("uuid=");
	int end = text.find("\"", start + 5);
	qy_uuid = text.substr(start + 5, end - (start + 5));
}

void saveQrcode()
{
	string str1 = "https://open.weixin.qq.com/connect/qrcode/";
	string url = str1 + qy_uuid;
	Response r3 = Get(Url(url));
	string savePath = "QY/qrCode.png";
	saveDataToFile(savePath, r3.text, true);
}

void get_wx_code()
{
	string str1 = "https://lp.open.weixin.qq.com/connect/l/qrconnect?uuid=";
	string str2 = "&last=404&_=1690524931570";
	string url = str1 + qy_uuid + str2;
	Response r4 = Get(Url(url));
	//cout << r4.text << endl;
	string text = r4.text;
	int start = text.find("wx_code='");
	int end = text.find("'", start + 9);
	qy_wx_code = text.substr(start + 9, end - (start + 9));
	//cout << "qy_wx_code: " << qy_wx_code << endl;
}

//key cookie
void get_cdb_auth()
{
	string str1 = "https://passport.qyer.com/oauth/weixin/callback?code=";
	string str2 = "&state=PASSPORT000064c35d02d13d3";
	string url = str1 + qy_wx_code + str2;
	Response r5 = Get(Url(url));
	auto cook = r5.cookies;
	for (auto a = cook.begin(); a != cook.end(); ++a)
	{
		//cout << a->first << ": " << a->second << endl;
		if (a->first == "cdb_auth")
		{
			cdb_auth = a->second;
		}
	}
	//cout << "cdb_auth: " << cdb_auth << endl;
}

void get_uid()
{
	string url = "https://www.qyer.com/qcross/home/ajax?action=notice&ajaxID=59015b9b733e86c93db2a17a";
	Response r6 = Post(Url(url), Header{
		{"Cookie", "cdb_auth=" + cdb_auth}
		});
	//cout << r6.text << endl;

	string text = r6.text;
	int start = text.find("u\\/");
	int end = text.find("\\", start + 3);
	uID = text.substr(start + 3, end - (start + 3));
	//cout << "uID: " << uID << endl;
}

void get_userMsg()
{
	//str1 = "https://www.qyer.com/u/";
	//url = str1 + uID;
	//Response r7 = Get(Url(url));
	//cout << r7.text << endl;
}

void get_userPhotos()
{
	string str1 = "https://photo.qyer.com/u";
	string url = str1 + uID;
	Response r8 = Get(Url(url));
	//cout << r8.text << endl;

	vector<string> img;
	string text = r8.text;
	int start = text.find(R"(<ul class="photo-lists">)");
	int end = text.find("</ul>", start + 24);
	string tmp = text.substr(start + 24, end - (start + 24));
	//cout << "------------------------------------------------------>>>>>>>>>>>>>>>" << endl;
	//cout << tmp << endl;
	//cout << tmp.length() << endl;

	int p = 0;
	int begin = 0;
	while (p < tmp.length())
	{
		int start = tmp.find(R"(data-id=")", begin);
		if (start == -1)
		{
			break;
		}
		int end = tmp.find("\"", start + 9);
		//cout << "start: " << start << endl;
		//cout << "end: " << end << endl;
		img.push_back(tmp.substr(start + 9, end - (start + 9)));
		p = end;
		p++;
		begin = p;
	}

	for (int i = 0; i < img.size(); ++i)
	{
		string str1 = "https://photo.qyer.com/";
		string str2 = "/allphoto";
		string url = str1 + img[i] + str2;

		Response tmp_r1 = Get(Url(url));
		string text = tmp_r1.text;
		//cout << text << endl;

		int start = text.find(R"(<img src="https://pic.qyer.com)");
		int end = text.find("\"", start + 10);
		url = text.substr(start + 10, end - (start + 10));

		Response tmp_r2 = Get(Url(url));
		//cout << url << endl;
		string savePath = "QY/UserPhotos/Img" + to_string(i + 1) + ".jpg";
		saveDataToFile(savePath, tmp_r2.text, true);
	}
}

void get_placePhotos()
{
	string placeTo;
	cin >> placeTo;

	string placeID;
	string type;
	for (int i = 0; i < 22; ++i)
	{
		if (!(place[i]->find(placeTo) == -1))
		{
			placeID = place[i][1];
			type = place[i][2];
			break;
		}
	}
	if (placeID == "")
	{
		cout << "很抱歉，还没有这个国家的照片" << endl;
		return;
	}
	//cout << "placeID: " << placeID << endl;
	//cout << "type: " << type << endl;

	for (int i = 0; i < 60; i += 30)
	{
		string str1 = "https://place.qyer.com/images.php?action=list&id=";
		string str2 = "&type=";
		string str3 = "&offset=";
		string str4 = "&limit=30";
		string url = str1 + placeID + str2 + type + str3 + to_string(i) + str4;
		Response r9 = Get(Url(url));
		//cout << "------------------------------------------------->>>>>>>>>>>>>>" << endl;
		//cout << r9.text << endl;
		//cout << "------------------------------------------------->>>>>>>>>>>>>>" << endl;

		vector<string> photos;
		string text = r9.text;
		json js = json::parse(text);
		auto objects = js["data"]["list"];
		for (auto obj : objects)
		{
			string tmp = obj["url"].dump();
			tmp = tmp.substr(1, tmp.length() - 2);
			photos.push_back(tmp);
		}
		for (int k = 0, j = i; j < i + 30; ++j, ++k)
		{
			//cout << photos[i] << endl;
			string url = photos[k];
			string savePath = "QY/PlacePhotos/" + placeTo + "/photo" + to_string(j + 1) + ".jpg";
			//cout << savePath << endl;
			Response tmp_r = Get(Url(url));
			string text = tmp_r.text;
			if (text.find("error") == -1)
			{
				saveDataToFile(savePath, text, true);
			}

		}
	}
	cout << "全部获取成功" << endl;
}

void *pthread_start(void* arg)
{
	//cout << "this is child pthread: " << endl;
	get_placePhotos();
	//cout << "------------------------------------------->>>>>>>>>>>>>" << endl;
	return NULL;
}

void dynamicGet()
{
	string url = "https://place.qyer.com/";
	Response r = Get(Url(url));

	const char* compressed_pointer = r.text.data();
	string decompressed_data = gzip::decompress(compressed_pointer, r.text.size());
	//cout << decompressed_data << endl;
	
	string text = decompressed_data;
	cout << text << endl;
	//cout << text.find("china") << endl;

	//saveDataToFile("backContent.txt", text, false);
	//
	//ifstream file("backContent.txt");
	//if (!file.is_open())
	//{
	//	cout << "open error" << endl;
	//}
	//else
	//{
	//	string buf;
	//	while (getline(file, buf))
	//	{
	//		int tmp = buf.find("china");
	//		if (tmp != -1)
	//		{
	//			cout << "找到了" << endl;
	//			break;
	//		}
	//	}
	//}
	//string place;
	////cin >> place;
	//int pos = text.find(place);
	//if (pos == -1)
	//{
	//	cout << "很抱歉，还没有这个国家的照片" << endl;
	//}
	//else
	//{
	//	string tmp = text.substr(pos - 200, 100);
	//	cout<< tmp <<endl;
	//}
}

string type, countryID, countryName;

void get_ID_type(string url)
{
	Response r = Get(Url(url));
	const char* compressed_pointer = r.text.data();
	string decompressed_data = gzip::decompress(compressed_pointer, r.text.size());
	string text = decompressed_data;
	
	int start = text.find("TYPE:'");
	int end = text.find("'", start + 6);
	type = text.substr(start + 6, end - (start + 6));

	start = text.find("COUNTRYID: '");
	end = text.find("'", start + 12);
	countryID = text.substr(start + 12, end - (start + 12));

	start = text.find("COUNTRYNAME: '");
	end = text.find("'", start + 14);
	countryName = text.substr(start + 14, end - (start + 14));

	cout << type << endl;
	cout << countryID << endl;
	cout << countryName << endl;

	for (int i = 0; i < 60; i += 30)
	{
		string str1 = "https://place.qyer.com/images.php?action=list&id=";
		string str2 = "&type=";
		string str3 = "&offset=";
		string str4 = "&limit=30";
		string url = str1 + countryID + str2 + type + str3 + to_string(i) + str4;
		Response r9 = Get(Url(url));
		//cout << "------------------------------------------------->>>>>>>>>>>>>>" << endl;
		//cout << r9.text << endl;
		//cout << "------------------------------------------------->>>>>>>>>>>>>>" << endl;

		vector<string> photos;
		string text = r9.text;
		json js = json::parse(text);
		auto objects = js["data"]["list"];
		for (auto obj : objects)
		{
			string tmp = obj["url"].dump();
			tmp = tmp.substr(1, tmp.length() - 2);
			photos.push_back(tmp);
		}
		for (int k = 0, j = i; j < i + 30; ++j, ++k)
		{
			//cout << photos[i] << endl;
			string url = photos[k];
			string savePath = "QY/PlacePhotos/" + countryName + "/photo" + to_string(j + 1) + ".jpg";
			//cout << savePath << endl;
			Response tmp_r = Get(Url(url));
			string text = tmp_r.text;
			if (text.find("error") == -1)
			{
				saveDataToFile(savePath, text, true);
			}
		}
	}
	cout << "all success!!!" << endl;
}

void Qy::fetchUserImg()
{
	setlocale(LC_ALL, "en_US.UTF-8");

	get_ID_type("https://place.qyer.com/usa/");

	//get_uuid();

	//saveQrcode();

	//Sleep(10000);

	//get_wx_code();

	//get_cdb_auth();

	//get_uid();

	//get_userMsg();

	//get_userPhotos();

	//pthread_t pthread1;
	//int ret1 = pthread_create(&pthread1, NULL, pthread_start, NULL);
	//if (ret1 == -1)
	//{
	//	cout << "pthread1 creating error" << endl;
	//}

	//Sleep(100);
	//pthread_t pthread2;
	//int ret2 = pthread_create(&pthread2, NULL, pthread_start, NULL);
	//if (ret2 == -1)
	//{
	//	cout << "pthread2 creating error" << endl;
	//}

	//Sleep(100);
	//pthread_t pthread3;
	//int ret3 = pthread_create(&pthread3, NULL, pthread_start, NULL);
	//if (ret3 == -1)
	//{
	//	cout << "pthread3 creating error" << endl;
	//}

	////cout << "this is main pthread: " << endl;
	//get_placePhotos();

	//pthread_join(pthread1, NULL);
	//pthread_join(pthread2, NULL);
	//pthread_join(pthread3, NULL);


	//dynamicGet();

}
