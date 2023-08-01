#include "SubUIDialog.h"

#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsDropShadowEffect>

CSubUIDialog::CSubUIDialog(QWidget* parent)
	: QDialog(parent)
{
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint | Qt::Dialog);

	initDialogUi();

	loadStyle(initDialogStyle());
}

CSubUIDialog::~CSubUIDialog()
{
}

void CSubUIDialog::setDialogTitle(const QString& strTitle)
{
	auto label = this->findChild<QLabel*>("uiDialogTitle");
	if (nullptr != label)
	{
		label->setText(strTitle);
		label->adjustSize();
	}
}

QString CSubUIDialog::getDialogTitle() const
{
	auto label = this->findChild<QLabel*>("uiDialogTitle");
	if (nullptr != label)
	{
		return label->text();
	}

	return "";
}

void CSubUIDialog::setClientLayout(QVBoxLayout* layout)
{
	if (nullptr != m_pClientArea)
	{
		m_pClientArea->setLayout(layout);
	}
}

QWidget* CSubUIDialog::getClientArea() const
{
	return m_pClientArea;
}

void CSubUIDialog::loadStyle(const QString& strStyle)
{
	this->style()->unpolish(this);
	auto strDestStyle = this->styleSheet() + strStyle;
	this->setStyleSheet(strDestStyle);
	this->style()->polish(this);
}

void CSubUIDialog::paintEvent(QPaintEvent* event)
{
	QStyleOption opt;
	opt.init(this);

	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void CSubUIDialog::resizeEvent(QResizeEvent* event)
{
	QDesktopWidget* desktopWidget = QApplication::desktop();
	if (nullptr == desktopWidget)
	{
		return QDialog::resizeEvent(event);
	}

	int primaryScreenIndex = desktopWidget->primaryScreen();
	QRect screenRect = desktopWidget->screenGeometry(primaryScreenIndex);
	int iScreenX = screenRect.width();
	int iScreenY = screenRect.height();

	move(iScreenX / 2 - width() / 2, iScreenY / 2 - height() / 2);
	return QDialog::resizeEvent(event);
}

void CSubUIDialog::keyPressEvent(QKeyEvent* event)
{
	return QDialog::keyPressEvent(event);
}

void CSubUIDialog::mouseMoveEvent(QMouseEvent* event)
{
	if (m_bMousePressed)
	{
		m_ptMouseMovePos = event->globalPos();
		this->move(this->pos() + m_ptMouseMovePos - m_ptMousePressPos);
		m_ptMousePressPos = m_ptMouseMovePos;
		return;
	}

	event->ignore();
}

void CSubUIDialog::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		QPoint curPoint = event->pos();
		auto label = this->findChild<QLabel*>("uiDialogTitle");
		if (nullptr != label)
		{
			if (curPoint.y() <= label->height())
			{
				m_ptMousePressPos = event->globalPos();
				m_bMousePressed = true;
			}
		}
	}

	event->ignore();
}

void CSubUIDialog::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bMousePressed = false;
	}

	event->ignore();
}

void CSubUIDialog::initDialogUi()
{
	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
	effect->setBlurRadius(15);
	effect->setXOffset(0);
	effect->setYOffset(0);
	effect->setColor(QColor(150, 150, 150, 180));

	QHBoxLayout* layout = new QHBoxLayout;
	layout->setContentsMargins(15, 15, 15, 15);
	layout->setSpacing(0);
	this->setLayout(layout);
	{
		QLabel* widget = new QLabel;
		widget->setObjectName("uiDialog");
		widget->setGraphicsEffect(effect);
		layout->addWidget(widget);
		{
			QVBoxLayout* vlayout = new QVBoxLayout;
			vlayout->setContentsMargins(0, 0, 0, 0);
			vlayout->setSpacing(0);
			widget->setLayout(vlayout);
			{
				vlayout->addWidget(createClientUi());
			}
		}
	}
}

//QWidget* CSubUIDialog::createTitleUi()
//{
//	QWidget* widget = new QWidget;
//	widget->setFixedHeight(44);
//	widget->setObjectName("uiDialogTitleArea");
//
//	QHBoxLayout* layout = new QHBoxLayout;
//	layout->setContentsMargins(24, 0, 16, 0);
//	layout->setSpacing(0);
//	// widget->setLayout(layout);
//	{
//		QLabel* title = new QLabel;
//		title->setObjectName("uiDialogTitle");
//		layout->addWidget(title);
//
//		layout->addStretch();
//
//		QPushButton* minBtn = new QPushButton;
//		minBtn->setFixedSize(24, 24);
//		minBtn->setFocusPolicy(Qt::NoFocus);
//		minBtn->setObjectName("uiDialogMinBtn");
//		layout->addWidget(minBtn);
//		connect(minBtn, &QPushButton::clicked, this, &CSubUIDialog::showMinimized);
//
//		QPushButton* closeBtn = new QPushButton;
//		closeBtn->setFixedSize(24, 24);
//		closeBtn->setFocusPolicy(Qt::NoFocus);
//		closeBtn->setObjectName("uiDialogCloseBtn");
//		layout->addWidget(closeBtn);
//		connect(closeBtn, &QPushButton::clicked, this, &CSubUIDialog::reject);
//
//	}
//
//	return widget;
//}

QWidget* CSubUIDialog::createClientUi()
{
	m_pClientArea = new QWidget;
	m_pClientArea->setObjectName("uiDialogClientArea");

	return m_pClientArea;
}

QString CSubUIDialog::initDialogStyle()
{
	QString strStyle = R"(
		#uiDialog{
			background-color: #ffffff;
			border-radius: 4px;
		}

		#uiDialogTitleArea{
			background-color: #2074f3;
			border-top-left-radius: 4px;
			border-top-right-radius: 4px;
		}

		#uiDialogClientArea{
			border: none;
			background-color: #ffffff;
			border-bottom-left-radius: 4px;
			border-bottom-right-radius: 4px;
		}

		#uiDialogTitle{
			border: none;
			font-family: "Microsoft YaHei";
			font-weight: normal;
			font-style: normal;
			font-size: 16px;
			color: #ffffff;
		}

		#uiDialogMinBtn{
			border-image: url(:/imagesrc/images/min_normal.png);
		}

		#uiDialogMinBtn:hover{
			border-image: url(:/imagesrc/images/min_hover.png);
		}

		#uiDialogMinBtn:pressed{
			border-image: url(:/imagesrc/images/min_pressed.png);
		}

		#uiDialogCloseBtn{
			border-image: url(:/imagesrc/images/close_normal.png);
		}

		#uiDialogCloseBtn:hover{
			border-image: url(:/imagesrc/images/close_hover.png);
		}

		#uiDialogCloseBtn:pressed{
			border-image: url(:/imagesrc/images/close_pressed.png);
		}
	)";

	return strStyle;
}
