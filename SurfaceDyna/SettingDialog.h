#pragma once
#include <qdialog.h>
#include "ui_SettingDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SettingDialogClass; };
QT_END_NAMESPACE

class QSettings;
class SettingDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SettingDialog(QWidget* parent = nullptr);
	~SettingDialog();

public:
	QString m_TsPath;
	QString m_DynaPath;
	QString m_FrameName;

private:
	QSettings* m_settings;

private:
	Ui::SettingDialogClass* ui;

	void tsPathSlot();
	void dynaPathSlot();
	void frameSlot();
	void closeSlot();
public:
	void freshPath();
};

