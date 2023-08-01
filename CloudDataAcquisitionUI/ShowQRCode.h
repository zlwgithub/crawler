#pragma once

#include <QtWidgets/QWidget>
#include "UI/Base/UIDialog.h"
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "CreateTaskUi.h"

class CShowQRCode : public QWidget
{
	Q_OBJECT

public:
	CShowQRCode(QWidget* parent);
	~CShowQRCode();

	void showqrcode(std::string);
	void QRCODE_CONFIRM_MSG_ACK_callback(QString);
public slots:
	void Popup_Scan();

private:
	QWidget* mainWidget = nullptr;
	QVBoxLayout* mainLayout = nullptr;
	QHBoxLayout* buttonLayout = nullptr;
	QPixmap* QrCode = nullptr;

	QLabel* imagelabel = nullptr;
	QLabel* AttentionLabel = nullptr;
	QLabel* Label1 = nullptr;
	QLabel* Label2 = nullptr;

	QPushButton* commitButton = nullptr;
};

