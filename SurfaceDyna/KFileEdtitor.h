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

private:
    //! 得到解析后的数据
    void getData();

    //! 双击树子节点弹出属性值
    void treeViewDoubleClick();
    //! 在TableWidget里面显示属性
    void treeViewClick();
        
    // 【测试用】
    void funDemo();

private:
    Ui::KFileEdtitorClass *ui;


public:
	//! 翻译json对象
    Translator* translator{ NULL };
    //! itemDialog对象
//     ItemDialog* itemdialog;

    //! 配置窗口对象
    SettingDialog* m_settingDialg{ NULL };

    DynaFrame* m_frame{ NULL };

    BT::BTExternalProgramEditor* m_dyna{ NULL };
public:
	//! 获取对话框数据并更新
	void freshData();
    //! 弹出数据
    void showMapDialog();
    void showPairDialog();
    //! 导出数据
    void exportData();
	//! 显示文件的树节点信息
	void displayItem();

    void readOverSlot(Data* re);

    void settingSlot();

    void openDynaSlot();
    void closeDynaSlot();

private:
    //! 文件节点树
    TreeWidget* treeWidget{ NULL };
    //! 节点树父节点
    QHash<QString, QTreeWidgetItem*> parentNodes;
    //! 文本内容
    DisplayWidget* displayWidget{ NULL };
    //! 弹出的对话框
    ItemDialog* itemDialog{ NULL };
    //! 读写文件
    ReadWrite* fileRW{ NULL };
    //! 读取的数据
    Data* data{ NULL };
};
