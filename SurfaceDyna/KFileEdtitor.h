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
    void setBtnsSize();

private:
    //! �õ������������
    void getData();

    //! ˫�����ӽڵ㵯������ֵ
    void treeViewDoubleClickSlot();
    //! ��TableWidget������ʾ����
    void treeViewClickSlot();
        
    // �������á�
    void funDemoSlot();

private:
    Ui::KFileEdtitorClass *ui;


public:
	//! ����json����
    Translator* m_translator{ NULL };
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
    void exportData();
	//! ��ʾ�ļ������ڵ���Ϣ
	void displayItem();

    void readOverSlot(Data* re);

    void settingSlot();

    void openDynaSlot();
    void closeDynaSlot();

    void menuTestSlot();

    void highlightLines(QTextBrowser* textBrowser, int lineNumber, int endNumber);
    void clearHighlightLines(QTextBrowser* textBrowser, int lineNumber, int endNumber);
    int last_start = 1, last_end = 1;

private:
    //! �ļ��ڵ���
    TreeWidget* m_treeWidget{ NULL };
    //! �ڵ������ڵ�
    QHash<QString, QTreeWidgetItem*> m_parentNodes;
    //! �ı�����
    DisplayWidget* m_displayWidget{ NULL };
    //! �����ĶԻ���
    ItemDialog* m_itemDialog{ NULL };
    //! ��д�ļ�
    ReadWrite* m_fileRW{ NULL };
    //! ��ȡ������
    Data* m_data{ NULL };
};
