#include "SettingDialog.h"
#include <QDebug>
#include <QCoreApplication>
#include <QSettings>
#include <QFileDialog>

SettingDialog::SettingDialog(QWidget* parent /*= nullptr*/)
	: QDialog(parent)
	, ui(new Ui::SettingDialogClass())
{
	ui->setupUi(this);
	setFixedSize(690, 291);

	connect(ui->btnTs, &QPushButton::clicked, this, &SettingDialog::tsPathSlot);
	connect(ui->btnDyna, &QPushButton::clicked, this, &SettingDialog::dynaPathSlot);
	connect(ui->btnFrameName, &QPushButton::clicked, this, &SettingDialog::frameSlot);
	QString configpath = "./setting/config.ini";
	m_settings = new QSettings(configpath, QSettings::IniFormat);
// 	settings = new QSettings("./setting/config.ini", QSettings::IniFormat);

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
// 	auto tspath = ui->editTsPath->text();
	QString tspath = QFileDialog::getOpenFileName(// 正常加载
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
// 	auto dypath = ui->editDynaPath->text();
	QString dypath = QFileDialog::getOpenFileName(// 正常加载
		this, u8"选择Manager文件",
		".",
		"exe files (*.exe);;All files (*.*)");
	if (dypath == "") return;
	ui->editDynaPath->setText(dypath);
	m_settings->setValue("DynaPath", dypath);
	m_settings->sync();
}

void SettingDialog::frameSlot()
{
	auto fNmae = ui->editFrameName->text();

	m_settings->setValue("FrameName", fNmae);
	m_settings->sync();
}

void SettingDialog::freshPath()
{
	m_TsPath = m_settings->value("TsPath").toString();
	m_DynaPath = m_settings->value("DynaPath").toString();
	m_FrameName = m_settings->value("FrameName").toString();
}
