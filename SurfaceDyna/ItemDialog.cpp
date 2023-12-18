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
	m_save = new QPushButton(u8"保存", this);
	m_cacel = new QPushButton(u8"取消", this);
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
	//! 储存对话框里面的QMap键值信息
	QMap<QString, QString >* kv = new QMap<QString, QString>;

	//! 遍历所有Label控件和TextEdit控件
	QList<QLabel*> labelList = this->findChildren<QLabel*>(); // 有顺序
	QList<QLineEdit*> lineEditList = this->findChildren<QLineEdit*>(); // 有顺序

// 	m_onlyValue = this->findChildren<QLineEdit*>();

	//! 把键值信息写入到QMap中
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
	//! 关闭当前窗体
	this->close();
	
}

