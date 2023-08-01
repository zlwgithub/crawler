#ifndef CLOUDDATAACQUISITIONUI_LISTTASKCARDUI
#define CLOUDDATAACQUISITIONUI_LISTTASKCARDUI

#pragma once
#include <QWidget>
#include"UI/Base/UIDialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QScrollBar>

class CListTaskCardUi : public CUIDialog
{
	Q_OBJECT;

public:
	CListTaskCardUi(QWidget* parent = nullptr);
	~CListTaskCardUi();

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	void initUi();
};

#endif  // CLOUDDATAACQUISITIONUI_LISTTASKCARDUI

