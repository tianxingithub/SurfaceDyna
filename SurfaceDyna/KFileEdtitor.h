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
//! 主界面类
class KFileEdtitor : public QMainWindow
{
    Q_OBJECT

public:
    KFileEdtitor(QWidget *parent = nullptr);
    ~KFileEdtitor();
    void addPlot();
    void setBtnsSize();

private:
    //! 得到解析后的数据
    void getData();

    //! 双击树子节点弹出属性值
    void treeViewDoubleClickSlot();
    //! 在TableWidget里面显示属性
    void treeViewClickSlot();
        
    // 【测试用】
    void funDemoSlot();

private:
    Ui::KFileEdtitorClass *ui;


public:
	//! 翻译json对象
    Translator* m_translator{ NULL };
    //! itemDialog对象
//     ItemDialog* itemdialog;

    //! 配置窗口对象
    SettingDialog* m_settingDialg{ NULL };

    DynaFrame* m_frame{ NULL };

    BT::BTExternalProgramEditor* m_dyna{ NULL };
public:
	//! 获取对话框数据并更新
	void freshData();
    //! 导出数据
    void exportData();
	//! 显示文件的树节点信息
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
    //! 文件节点树
    TreeWidget* m_treeWidget{ NULL };
    //! 节点树父节点
    QHash<QString, QTreeWidgetItem*> m_parentNodes;
    //! 文本内容
    DisplayWidget* m_displayWidget{ NULL };
    //! 弹出的对话框
    ItemDialog* m_itemDialog{ NULL };
    //! 读写文件
    ReadWrite* m_fileRW{ NULL };
    //! 读取的数据
    Data* m_data{ NULL };
};
