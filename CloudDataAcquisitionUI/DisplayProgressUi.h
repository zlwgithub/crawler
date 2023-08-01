#ifndef CLOUDDATAACQUISITIONUI_DISPLAYPROGRESSUI
#define CLOUDDATAACQUISITIONUI_DISPLAYPROGRESSUI

#pragma once

#include <QWidget>
#include"UI/Base/SubUIDialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QScrollBar>

class CDisplayProgressUi : public CSubUIDialog
{
	Q_OBJECT;

public:
	CDisplayProgressUi(QWidget* parent = nullptr);
	~CDisplayProgressUi();

private:
	// ½ø¶ÈÌõ
	QProgressBar* firstLayerProgressBar;
	QProgressBar* secondLayerProgressBar;

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	void initUi();
};
#endif  // CLOUDDATAACQUISITIONUI_DISPLAYPROGRESSUI
