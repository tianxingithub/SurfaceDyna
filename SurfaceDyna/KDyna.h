#pragma once

#include <QWidget>
#include "ui_KDyna.h"
#include "KFileEdtitor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class KDynaClass; };
QT_END_NAMESPACE

class KDyna : public QWidget
{
	Q_OBJECT

public:
	KDyna(QWidget *parent = nullptr);
	~KDyna();

private:
	KFileEdtitor* m_keditor{ NULL };
	
	bool m_btnState{ false }; // “开始”页面的显示状态


	void stateSlot();
	void tabChangedSlot();


private:
	Ui::KDynaClass *ui;
};
