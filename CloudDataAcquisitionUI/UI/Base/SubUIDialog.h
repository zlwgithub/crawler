#ifndef CLOUDDATAACQUISITIONUI_UI_BASE_SUBUIDIALOG_H
#define CLOUDDATAACQUISITIONUI_UI_BASE_SUBUIDIALOG_H

#pragma once

#include <QDialog>

class QVBoxLayout;  // Ç°ÖÃÉùÃ÷

class  CSubUIDialog : public QDialog
{
	Q_OBJECT

public:
	CSubUIDialog(QWidget* parent = nullptr);
	~CSubUIDialog();

public:
	void setDialogTitle(const QString& strTitle);
	QString getDialogTitle() const;

	void setClientLayout(QVBoxLayout* layout);
	int getShadowWidth() const { return 15; }

public:
	QWidget* getClientArea() const;
	void loadStyle(const QString& strStyle);

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void resizeEvent(QResizeEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);

private:
	void initDialogUi();
	// QWidget* createTitleUi();
	QWidget* createClientUi();
	QString initDialogStyle();

private:
	QWidget* m_pClientArea{ nullptr };

private:
	QPoint m_ptMousePressPos;
	QPoint m_ptMouseMovePos;
	QPoint m_ptResizePressPos;
	QSize m_sizeResizePress;
	bool m_bMousePressed{ false };
	bool m_bMouseResizePressed{ false };
	bool m_bOpenStrech{ false };
};

#endif // CLOUDDATAACQUISITIONUI_UI_BASE_SUBUIDIALOG_H

