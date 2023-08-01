#include "CloudDataAcquisitionUI.h"
#include "TaskUi.h"
#include "TaskCardUi.h"
#include "CreateTaskUi.h"
#include "DisplayProgressUi.h"
#include "ShowResultsUi.h"
#include "ShowQRCode.h"

#include <QtWidgets/QApplication>
#include <QPushButton>  
#include <QVBoxLayout>  // ´¹Ö±²¼¾Ö
#include <QHBoxLayout>

#include <QtWidgets>

#include <QProcess>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "StartTaskUi.h"
#include"service.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	//Service::getInstance();

	QProcess p;
	//QStringList list;
	//list.push_back(R"(E:\Release\crawler.exe)");
	//p.setArguments(list);
	p.start(R"(E:\Release\crawler.exe)");
	p.waitForStarted();
	int iPID = p.processId();

	QStringList args;
	args << "/F";
	args << "/T";
	args << "/PID";
	args << QString("%1").arg(iPID);
	QProcess::execute("taskkill", args); 

	CloudDataAcquisitionUI::getInstance().show();

	return a.exec();
}
