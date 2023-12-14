#pragma once

#include <QWidget>
#include "ui_DisplayWidget.h"
#include "QTextBrowser"

QT_BEGIN_NAMESPACE
namespace Ui { class DisplayWidgetClass; };
QT_END_NAMESPACE

//! �ı���ʾ����
class DisplayWidget : public QWidget
{
	Q_OBJECT

public:
	DisplayWidget(QWidget *parent = nullptr);
	~DisplayWidget();

private:
	Ui::DisplayWidgetClass *ui;
public:
	//! ��ʾ�ļ��ؼ�
	QTextBrowser* textDisplay;
	//! ��ֱ����
	//QVBoxLayout* layout;
};
