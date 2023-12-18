#include "ItemDialog.h"
#include "qlayout.h"
#include "QLabel"
#include "QLineEdit"
#include "QDebug"
#include <QTextEdit>

ItemDialog::ItemDialog(QWidget*parent)
	: QDialog(parent)
	, ui(new Ui::ItemWidgetClass())
{
	m_save = new QPushButton(u8"����", this);
	m_cacel = new QPushButton(u8"ȡ��", this);
	m_save->setVisible(false);
	m_cacel->setVisible(false);
	
	m_dialogMapData = nullptr;
	m_krows = nullptr;
	m_vrows = nullptr;
	//onlyValue = nullptr;

	ui->setupUi(this);
	connect(this->m_save, &QPushButton::clicked, this, &ItemDialog::getDialogDataSlot);
	//connect(this->save, &QPushButton::clicked, new KFileEdtitor(), &KFileEdtitor::freshData);
	connect(this->m_cacel, &QPushButton::clicked, this, &QWidget::close);
}

ItemDialog::~ItemDialog()
{
	delete ui;
}

void ItemDialog::getDialogDataSlot()
{
	//! ����Ի��������QMap��ֵ��Ϣ
	QMap<QString, QString >* kv = new QMap<QString, QString>;

	//! ��������Label�ؼ���TextEdit�ؼ�
	QList<QLabel*> labelList = this->findChildren<QLabel*>(); // ��˳��
	QList<QLineEdit*> lineEditList = this->findChildren<QLineEdit*>(); // ��˳��

// 	m_onlyValue = this->findChildren<QLineEdit*>();

	//! �Ѽ�ֵ��Ϣд�뵽QMap��
	m_krows = new QList<QString>;
	m_vrows = new QList<QString>;
// 	int kCount = labelList.size();

	for (int i = 0; i < lineEditList.size(); i++)
	{
		auto k = labelList.at(i*2)->text();
		auto v = lineEditList.at(i)->text();
		m_krows->append(k);
		m_vrows->append(v);
	}	

	QList<QTextEdit*> textEditList = this->findChildren<QTextEdit*>();
	m_notes = textEditList[0]->toPlainText();

	emit doubleClickSig();
	//! �رյ�ǰ����
	this->close();
	
}

