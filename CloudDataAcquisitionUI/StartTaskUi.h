#ifndef CLOUDDATAACQUISITIONUI_STARTTASKUI
#define CLOUDDATAACQUISITIONUI_STARTTASKUI

#pragma once
#include <QWidget>
#include"UI/Base/UIDialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QScrollBar>

class CStartTaskUi : public QWidget
{
	Q_OBJECT;

public:
	CStartTaskUi(QWidget* parent = nullptr);
	~CStartTaskUi();

private:
	// ½ø¶ÈÌõ
	QProgressBar* firstLayerProgressBar;
	QProgressBar* secondLayerProgressBar;
	// »¬ÂÖ
	QScrollBar* scrollBar;

protected:
	void paintEvent(QPaintEvent* event) override;
	void START_CRAWL_MSG_ACK_callback(QString);
private slots:
	void showResults();


private:
	void initUi();

	std::string dbname;
};

#endif  // CLOUDDATAACQUISITIONUI_STARTTASKUI