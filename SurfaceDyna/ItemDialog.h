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

//! ˫���ڵ㵯���ĶԻ���
class ItemDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ItemDialog(QWidget*parent = nullptr);
	~ItemDialog();

public:
	QPushButton* m_save;
	QPushButton* m_cacel;

	//! �Ի�������ؼ���QMap
	QMap<QString, QString >* m_dialogMapData;

	//! �Ի�������ؼ���k
	QList<QString>* m_krows;
	//! �Ի�������ؼ���v
	QList<QString>* m_vrows;

	//! �Ի������ע��Ϣ
	QString m_notes;

// 	//! �޸Ŀ������ֵ
// 	QList<QLineEdit*> m_onlyValue;

public:
	//! �õ��Ի�������ؼ�����Ϣ
	void getDialogDataSlot();

signals:
	//! ���ݱ��������Ϣ
	void doubleClickSig();
private:
	Ui::ItemWidgetClass *ui;
};
