#pragma once

#include <QtWidgets/QMainWindow>
#include <QHash>
#include "ui_KFileEdtitor.h"
#include "TreeWidget.h"
#include "DisplayWidget.h"
#include "ReadWrite.h"
#include "ItemDialog.h"
#include "QJsonObject"
#include "Translator.h"
#include "SettingDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class KFileEdtitorClass; };
QT_END_NAMESPACE

class Data;
class DynaFrame;
namespace BT {
	class BTExternalProgramEditor;
}
//! ��������
class KFileEdtitor : public QMainWindow
{
    Q_OBJECT

public:
    KFileEdtitor(QWidget *parent = nullptr);
    ~KFileEdtitor();
    void addPlot();

private:
    //! �õ������������
    void getData();

    //! ˫�����ӽڵ㵯������ֵ
    void treeViewDoubleClick();
    //! ��TableWidget������ʾ����
    void treeViewClick();
        
    // �������á�
    void funDemo();

private:
    Ui::KFileEdtitorClass *ui;


public:
	//! ����json����
    Translator* translator{ NULL };
    //! itemDialog����
//     ItemDialog* itemdialog;

    //! ���ô��ڶ���
    SettingDialog* m_settingDialg{ NULL };

    DynaFrame* m_frame{ NULL };

    BT::BTExternalProgramEditor* m_dyna{ NULL };
public:
	//! ��ȡ�Ի������ݲ�����
	void freshData();
    //! ��������
    void showMapDialog();
    void showPairDialog();
    //! ��������
    void exportData();
	//! ��ʾ�ļ������ڵ���Ϣ
	void displayItem();

    void readOverSlot(Data* re);

    void settingSlot();

    void openDynaSlot();
    void closeDynaSlot();

private:
    //! �ļ��ڵ���
    TreeWidget* treeWidget{ NULL };
    //! �ڵ������ڵ�
    QHash<QString, QTreeWidgetItem*> parentNodes;
    //! �ı�����
    DisplayWidget* displayWidget{ NULL };
    //! �����ĶԻ���
    ItemDialog* itemDialog{ NULL };
    //! ��д�ļ�
    ReadWrite* fileRW{ NULL };
    //! ��ȡ������
    Data* data{ NULL };
};
