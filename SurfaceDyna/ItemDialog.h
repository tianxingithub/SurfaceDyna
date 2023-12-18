#pragma once

#include <QWidget>
#include "ui_ItemDialog.h"
#include "qpushbutton.h"
#include "QDialog"
#include "QLineEdit"
#include "QPair"

QT_BEGIN_NAMESPACE
namespace Ui { class ItemWidgetClass; };
QT_END_NAMESPACE

//! 双击节点弹出的对话框
class ItemDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ItemDialog(QWidget*parent = nullptr);
	~ItemDialog();

public:
	QPushButton* m_save;
	QPushButton* m_cacel;

	//! 对话框里面控件的QMap
	QMap<QString, QString >* m_dialogMapData;

	//! 对话框里面控件的k
	QList<QString>* m_krows;
	//! 对话框里面控件的v
	QList<QString>* m_vrows;

	//! 对话框的批注信息
	QString m_notes;

// 	//! 修改框里面的值
// 	QList<QLineEdit*> m_onlyValue;

public:
	//! 得到对话框里面控件的信息
	void getDialogDataSlot();

signals:
	//! 数据保存后发送消息
	void doubleClickSig();
private:
	Ui::ItemWidgetClass *ui;
};
