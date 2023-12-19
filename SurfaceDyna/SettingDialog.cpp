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
		this, u8"选择翻译配置文件",
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
		this, u8"选择Manager文件",
		".",
		"exe files (*.exe);;All files (*.*)");
	if (dypath == "")
	{
		QMessageBox::information(this, u8"错误", u8"选择Manager.exe失败！");

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
		QMessageBox::information(this, u8"错误", u8"未写入窗体名称！");
		return;
	}

	QMessageBox::information(this, u8"提示", u8"窗体名称已保存！");

	m_settings->setValue("FrameName", fNmae);
	m_settings->sync();
}

void SettingDialog::closeSlot()
{
	auto fNmae = ui->editFrameName->text();
	if (fNmae == "")
	{
		QMessageBox::information(this, u8"错误", u8"未写入窗体名称！");
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
