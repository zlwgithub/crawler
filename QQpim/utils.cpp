#include "utils.h"
#include<iostream>
#include <wchar.h>
#include <windows.h>
#include <string>
using namespace std;
utils::utils() {

}

utils::~utils() {

}

//string utils::hash33(string qrsig) {
//	//hash 33，解密ptqrtoken
//	int e = 0;
//	for (int i = 0; i < qrsig.length(); i++) {
//		e += (e << 5) + qrsig[i];
//	}
//	return to_string(e & 2147483647);
//}

std::string utils::string_To_UTF8(const std::string& str) {

	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;


}


