#include "SettingDialog.h"
#include <QDebug>
#include <QCoreApplication>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>

SettingDialog::SettingDialog(QWidget* parent /*= nullptr*/)
	: QDialog(parent)
	, ui(new Ui::SettingDialogClass())
{
	ui->setupUi(this);
	setFixedSize(690, 291);

	connect(ui->btnTs, &QPushButton::clicked, this, &SettingDialog::tsPathSlot);
	connect(ui->btnDyna, &QPushButton::clicked, this, &SettingDialog::dynaPathSlot);
	connect(ui->btnFrameName, &QPushButton::clicked, this, &SettingDialog::frameSlot);
	connect(ui->btnClose, &QPushButton::clicked, this, &SettingDialog::closeSlot);
	QString configpath = "./setting/config.ini";
	m_settings = new QSettings(configpath, QSettings::IniFormat);

	freshPath();

	ui->editTsPath->setText(m_TsPath);
	ui->editDynaPath->setText(m_DynaPath);
	ui->editFrameName->setText(m_FrameName);
}

SettingDialog::~SettingDialog()
{

}

void SettingDialog::tsPathSlot()
{
	QString tspath = QFileDialog::getOpenFileName(
		this, u8"ѡ���������ļ�",
		".",
		"json files (*.json);;All files (*.*)");
	if (tspath == "") return;
	ui->editTsPath->setText(tspath);
	m_settings->setValue("TsPath", tspath);
	m_settings->sync();

}

void SettingDialog::dynaPathSlot()
{
	QString dypath = QFileDialog::getOpenFileName(
		this, u8"ѡ��Manager�ļ�",
		".",
		"exe files (*.exe);;All files (*.*)");
	if (dypath == "")
	{
		QMessageBox::information(this, u8"����", u8"ѡ��Manager.exeʧ�ܣ�");

		return;
	}
	ui->editDynaPath->setText(dypath);
	m_settings->setValue("DynaPath", dypath);
	m_settings->sync();
}

void SettingDialog::frameSlot()
{
	auto fNmae = ui->editFrameName->text();
	if (fNmae == "")
	{
		QMessageBox::information(this, u8"����", u8"δд�봰�����ƣ�");
		return;
	}

	QMessageBox::information(this, u8"��ʾ", u8"���������ѱ��棡");

	m_settings->setValue("FrameName", fNmae);
	m_settings->sync();
}

void SettingDialog::closeSlot()
{
	auto fNmae = ui->editFrameName->text();
	if (fNmae == "")
	{
		QMessageBox::information(this, u8"����", u8"δд�봰�����ƣ�");
		return;
	}
	m_settings->setValue("FrameName", fNmae);
	m_settings->sync();


	this->close();

}

void SettingDialog::freshPath()
{
	m_TsPath = m_settings->value("TsPath").toString();
	m_DynaPath = m_settings->value("DynaPath").toString();
	m_FrameName = m_settings->value("FrameName").toString();
}
