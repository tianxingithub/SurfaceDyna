#pragma once

#include <QWidget>
#include "ui_DynaFrame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DynaFrameClass; };
QT_END_NAMESPACE
namespace BT {
	class BTExternalProgramEditor;
}
class QPushButton;

class DynaFrame : public QWidget
{
	Q_OBJECT

public:
	DynaFrame(QWidget *parent = nullptr);
	~DynaFrame();
	void setDyna(BT::BTExternalProgramEditor* dyna);
	void setDyna(QPushButton* dyna);
private:
	Ui::DynaFrameClass *ui;

protected:
	// ��д�ر��¼�
	void closeEvent(QCloseEvent* event) override;

signals:
	void DynaCloseSig();
};
