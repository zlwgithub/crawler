#ifndef DEAL_DATA_H 
#define DEAL_DATA_H 

#include<iostream>
#include <qstring.h>
using namespace std;

class dealData
{

public:
	dealData();
	~dealData();

public:

	bool dealJson(QString filepath);

	bool dealJsonStringContact(QString jsonString);

	bool dealJsonTel(QString filepath);

	bool dealJsonStringTel(QString jsonString);

	bool dealDataBaseContact();

	bool dealDataBaseTel();





private:



};


#endif
