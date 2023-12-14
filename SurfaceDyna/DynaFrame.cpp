#include "DynaFrame.h"
#include "BTExternalProgramEditor.h"
#include <QPushButton>

DynaFrame::DynaFrame(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::DynaFrameClass())
{
	ui->setupUi(this);
}

DynaFrame::~DynaFrame()
{
	delete ui;
}

void DynaFrame::setDyna(BT::BTExternalProgramEditor* dyna)
{
	ui->verticalLayout->addWidget(dyna);
}

void DynaFrame::setDyna(QPushButton* dyna)
{
	ui->verticalLayout->addWidget(dyna);
}

void DynaFrame::closeEvent(QCloseEvent* event)
{
	emit DynaCloseSig();
	// 调用父类的关闭事件处理
	QWidget::closeEvent(event);
}
