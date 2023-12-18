#include "KFileEdtitor.h"
#include "qfiledialog.h"
#include <QHeaderView>
#include "qlabel.h"
#include "QLineEdit"
#include "ReadThread.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "BTExternalProgramEditor.h"
#include "DynaFrame.h"
#include "Data.h"
#include <QWindow>


KFileEdtitor::KFileEdtitor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::KFileEdtitorClass())
{
    ui->setupUi(this);

	fileRW = new ReadWrite();
	data = nullptr;
	itemDialog = nullptr;
    m_settingDialg = nullptr;
    m_settingDialg = new SettingDialog(this);

    treeWidget = new TreeWidget(ui->centralWidget);
    treeWidget->setMinimumSize(250, 600);
    ui->verticalLayout->addWidget(treeWidget);

    displayWidget = new DisplayWidget(ui->centralWidget);
    displayWidget->setMinimumSize(600, 500);
	ui->horizontalLayout->addWidget(displayWidget);

    translator = nullptr;
    auto tsPath = m_settingDialg->m_TsPath;
    translator = new Translator(tsPath);

    addPlot();
}

KFileEdtitor::~KFileEdtitor()
{
    delete ui;
}

void KFileEdtitor::addPlot()
{
	connect(fileRW, &ReadWrite::readFinishedSig, this, &KFileEdtitor::readOverSlot);
	connect(ui->actionSetting, &QAction::triggered, this, &KFileEdtitor::settingSlot);
	connect(ui->actionOpenDyna, &QAction::triggered, this, &KFileEdtitor::openDynaSlot);
	connect(ui->actionDynaClose, &QAction::triggered, this, &KFileEdtitor::closeDynaSlot);


    connect(ui->actionOpen, &QAction::triggered, this, &KFileEdtitor::getData);
    connect(ui->actionSave, &QAction::triggered, this, &KFileEdtitor::exportData);
    connect(treeWidget->treeItem, &QTreeWidget::doubleClicked, this, &KFileEdtitor::treeViewDoubleClick);
    connect(treeWidget->treeItem, &QTreeWidget::clicked, this, &KFileEdtitor::treeViewClick);


}

void KFileEdtitor::funDemo()
{
    QMap<QString, QMap<QString, QString>>m;
    m.insert(QString("a"), QMap<QString, QString>());
    auto mm = m["b"];


}

void KFileEdtitor::getData()
{
    QString filepath = QFileDialog::getOpenFileName(// 正常加载
        this, u8"打开K文件",
        ".",
        "k files (*.k);;All files (*.*)");
    if (filepath == nullptr)
        return;

    if (data)
    {
        delete data;
        data = nullptr;
        displayWidget->textDisplay->clear();
        treeWidget->treeItem->clear();
        treeWidget->initTree();
        parentNodes = QHash<QString, QTreeWidgetItem*>();
    }
    
    /*this->data = */fileRW->readData(filepath, displayWidget->textDisplay);
//     displayItem();
}

void KFileEdtitor::exportData()
{
	auto obj = dynamic_cast<ReadThread*>(sender());
	if (obj)
	{
		this->data = obj->data;
	}
    if (data == nullptr)
        return;
    QString filepath = QFileDialog::getSaveFileName(this, u8"保存K文件",
        ".",
        "k files (*.k);;all files(*.*)");
    fileRW->writeDataRoot(filepath,data);

}

void KFileEdtitor::displayItem()
{
    if (data == nullptr)
        return;
    treeWidget->treeItem->setRootIsDecorated(false);
    auto parent_nodes = data->rootOrder;

    foreach (auto s , *(data->rootOrder))
    {
        auto a = data->rootMap->value(s);
        if (a==nullptr)
            continue;
        QStringList parts = s.split("_");
        QString parentName = parts[0]; // 获取父节点名称

		// 检查父节点是否已存在，如果不存在则创建
        if (!parentNodes.contains(parentName))
        {
            QTreeWidgetItem* parentNode = new QTreeWidgetItem(treeWidget->root);
            parentNode->setText(0, parentName);
            parentNode->setIcon(0, QIcon("./images/fir.png"));
            parentNodes[parentName] = parentNode;
        }

        QTreeWidgetItem* childItem1 = new QTreeWidgetItem(parentNodes[parentName]);
        childItem1->setIcon(0, QIcon("./images/sec.png"));
        childItem1->setText(0, s.mid(parentName.size()+1));
    }
    treeWidget->treeItem->expandAll();  // 展开所有节点
    treeWidget->treeItem->sortItems(0, Qt::AscendingOrder);
}

void KFileEdtitor::readOverSlot(Data*re)
{
    int a = 1;
	
    this->data = re;
    displayItem();
}

void KFileEdtitor::settingSlot()
{
    m_settingDialg->show();
}


void KFileEdtitor::openDynaSlot()
{
    if (m_frame == NULL)
    {
        m_frame = new DynaFrame();
		connect(m_frame, &DynaFrame::DynaCloseSig, this, &KFileEdtitor::closeDynaSlot);
    }

    m_frame->show();

    QString frameName = m_settingDialg->m_FrameName;
    if (m_dyna == NULL)
    {
        m_settingDialg->freshPath();
		auto dynaPath = m_settingDialg->m_DynaPath;
		auto nowPath = QCoreApplication::applicationDirPath();

		m_dyna = new BT::BTExternalProgramEditor(dynaPath, nowPath
            , ""//u8"Afx:00400000:8:00010003:00000000:03661627"
			, frameName
		);
 		m_dyna->startExternalProgram();
		QThread::msleep(300);
		m_frame->setDyna(m_dyna);
    
		LPCWSTR myLPCWSTR = reinterpret_cast<LPCWSTR>(frameName.utf16());
		HWND hwnd = FindWindow(nullptr, myLPCWSTR);

		if (hwnd)
		{
			// 获取窗体当前样式
			LONG style = GetWindowLong(hwnd, GWL_STYLE);

			// 最大化窗口
			ShowWindow(hwnd, SW_MAXIMIZE);

			// 隐藏标题栏
			SetWindowLong(hwnd, GWL_STYLE, style & ~WS_CAPTION);

			// 使改变生效
			SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

		}

    }


}

void KFileEdtitor::closeDynaSlot()
{
    if (m_frame)
    {
		m_frame->hide();
		m_frame = NULL;

    }

    if (m_dyna)
    {
// 		delete m_dyna;
        
        m_dyna->closeExternalProgram();
		m_dyna = NULL;
    }

}

void KFileEdtitor::treeViewDoubleClick()
{
    //showMapDialog();
    showPairDialog();
    //freshData();
}



void KFileEdtitor::showPairDialog()
{
	if (this->data == nullptr)
		return;
	QTreeWidgetItem* item = treeWidget->treeItem->currentItem();
	QString item_text = item->text(0);

	if (item_text == u8"激活能量数值") return;

	QString key = item->text(0);
    QString parent_text;
    
    if (item->parent())
    {
        parent_text = item->parent()->text(0);
        if (parent_text == u8"激活能量数值" || item->text(0) == "" || item_text == u8"激活能量数值")
            return;

        // 	if (key == u8"激活能量数值") return;
        key = parent_text +"_" + key;
        itemDialog = new ItemDialog(this);
        //(parent_text + "_" + item_text.mid(0, item_text.length() -5)));
//         itemDialog->setWindowTitle(parent_text + "_" + item_text.mid(0, item_text.length() - 5));
        itemDialog->setWindowTitle(key);
        connect(itemDialog, &ItemDialog::doubleClickSig, this, &KFileEdtitor::treeViewClick);

        auto kvPair = data->rootMap->value(key);
        auto item_index = data->rootOrder->indexOf(key);
        auto item_notes = data->rootOrder_notes->at(item_index);
        qDebug() << "--------------------------" << item_notes;
        auto kRow = kvPair->first;
        auto vRow = kvPair->second;

        if (kRow.size() == 0)
        {
            qDebug() << "数据出错，k.size()=0,属性无值";
            return;
        }
        int w = 90, h = 30, px = 10, py = 40;
        int numCount = 0;
        int rowCount = 0;

        int py_tr_v = 0;
        int py_tr_k = 0;
        for (auto row : kRow)//遍历第一行的属性
        {
            for (int i = 0; i < row.size(); i++)
            {
                auto k = row[i];
                int kcount = kRow.last().size() <= 8 ? 8 : kRow.last().size();

                QLabel* label = new QLabel(itemDialog);
                QLabel* label_tr = new QLabel(itemDialog);
                py_tr_v = (rowCount + 1) * (h - 16);
                if (rowCount == 0)
                {
                    py_tr_k = rowCount * h;
                }
                else
                {
                    py_tr_k = rowCount * (h - 16);
                }
                //! 配置中文
                if (translator->json != nullptr)
                {
                    QString jLable = translator->json->value(k).toString();
                    if (jLable != "")
                    {
                        label->setText(k);
                        label_tr->setText(jLable);
                    }
                    else
                    {
                        label->setText(k);
                        label_tr->setText(k);
                    }
                }
                else
                {
                    label->setText(k);
                    label_tr->setText(k);
                }

                // 如果Lable是unused直接放在最后面
                if (k.mid(0, 6) == "unused")
                {
                    label->setGeometry((w + px) * (kcount - 1) + 45, (h + py) * rowCount + py_tr_k, w, h);
//                     label->setAlignment(Qt::AlignCenter);
                    label_tr->setGeometry((w + px) * (kcount - 1) + 45, (h + py) * rowCount + py_tr_v, w, h);
//                     label_tr->setAlignment(Qt::AlignCenter);
                }
                else
                {
                    label->setGeometry((w + px) * i + 45, (h + py) * rowCount + py_tr_k, w, h);
//                     label->setAlignment(Qt::AlignCenter);
                    label_tr->setGeometry((w + px) * i + 45, (h + py) * rowCount + py_tr_v, w, h);
//                     label_tr->setAlignment(Qt::AlignCenter);
                }


                //! 把unused属性的值设置为不可修改的textBrowser
                if (k.mid(0, 6) == "unused")
                {
                    QLineEdit* value = new QLineEdit(itemDialog);
                    value->setReadOnly(true); // 设置为只读
                    value->setText(vRow[rowCount][i]);
                    value->setAlignment(Qt::AlignCenter);
                    value->setGeometry((w + px) * (kcount - 1) + 45, (h + py) * rowCount + py_tr_v + 35, w, h);
                }
                else
                {
                    QLineEdit* value = new QLineEdit(itemDialog);
                    value->setText(vRow[rowCount][i]);
                    value->setGeometry((w + px) * i + 45, (h + py) * rowCount + py_tr_v + 35, w, h);
                }

            }
            rowCount++;
        }

        int xcount = kRow.last().size() <= 8 ? 8 : kRow.last().size();

        int xx = (w + px) * (xcount + 1) - 20;
        int yy = (h + py) * (kRow.size() + 1) + 50 + py_tr_v;

        // 显示节点批注
        if (item_notes != " ")
        {
            yy += 30;
			QTextBrowser* textBro_notes = new QTextBrowser(itemDialog); //item_notes
			textBro_notes->setGeometry(45, yy - 140, 790, 80); // 设置 QTextBrowser 的位置和大小
			textBro_notes->setPlainText(item_notes);            
        }
        else
        {
            yy -= 60;
        }

        itemDialog->resize(xx, yy);
        itemDialog->setFixedSize(xx, yy);
        itemDialog->save->move(xx - 235, yy - 45);
        itemDialog->save->resize(w, h);
        itemDialog->save->setVisible(true);
        itemDialog->cacel->move(xx - 135, yy - 45);
        itemDialog->cacel->resize(w, h);
        itemDialog->cacel->setVisible(true);

        itemDialog->show();
    }
}

void KFileEdtitor::showMapDialog()
{
    if (this->data == nullptr)
        return;
    QTreeWidgetItem* item = treeWidget->treeItem->currentItem();
    QString key = item->text(0);
    if (key == u8"激活能量数值")return;

    itemDialog = new ItemDialog(this);
    itemDialog->setWindowTitle(key);

    int numCount = 0;
    int w = 90, h = 30, px = 10, py = 40;

    QMap<QString, QString>* kv = nullptr;
    QList<QString>* attOrder = nullptr;


    if (kv == nullptr || attOrder == nullptr)
        return;

    for each (auto k in *attOrder)
    {
        QLabel* label = new QLabel(itemDialog);
        QLabel* label_tr = new QLabel(itemDialog);
        //! 配置中文
        if (translator != nullptr)
        {
            QString jLable = translator->json->value(k).toString();
            if (jLable != "")
            {
                label->setText(k);
                label_tr->setText(jLable);
            }
            else
            {
                label->setText(k);
                label_tr->setText(k);
            }
        }
        else
        {
            label->setText(k);
            label_tr->setText(k);
        }

        //! 如果Lable是unused直接放在最后面
        if (k.mid(0, 6) == "unused")
        {
            label->setGeometry((w + px) * (7 % 8) + 45, (h + py) * (numCount / 8), w, h);
            label_tr->setGeometry((w + px) * (7 % 8) + 45, (h + py) * ((numCount / 8)+1), w, h);
            numCount = numCount + (7 - (numCount % 8));
        }
        else
        {
            label->setGeometry((w + px) * (numCount % 8) + 45, (h + py) * (numCount / 8), w, h);
            label_tr->setGeometry((w + px) * (numCount % 8) + 45, (h + py) * ((numCount / 8)+1), w, h);
        }

        //! 把unused属性的值设置为不可修改的textBrowser
        if (k.mid(0, 6) == "unused")
        {
            QTextBrowser* value = new QTextBrowser(itemDialog);
            value->setText(kv->value(k));
            value->setAlignment(Qt::AlignCenter);
            numCount = numCount - (7 - (numCount % 8));
            value->setGeometry((w + px) * (7 % 8) + 45, (h + py) * ((numCount / 8)+1) + 35, w, h);
            numCount = numCount + (7 - (numCount % 8));
        }
        else
        {
            QLineEdit* value = new QLineEdit(itemDialog);
            value->setText(kv->value(k));
            value->setGeometry((w + px) * (numCount % 8) + 45, (h + py) * ((numCount / 8)+1) + 35, w, h);
        }
        numCount++;
    }

    int xx = (w + px) * 9, yy = (h + py) * (numCount / 8 + 1) + 50;
    // 显示节点批注
    QTextBrowser* notes = new QTextBrowser(itemDialog);
//     notes->setsize
    itemDialog->resize(xx, yy);

    itemDialog->save->move(xx - 240, yy - 50);
    itemDialog->save->setVisible(true);
    itemDialog->cacel->move(xx - 140, yy - 50);
    itemDialog->cacel->setVisible(true);

    itemDialog->show();    
}

void KFileEdtitor::freshData()
{
    if (itemDialog == nullptr)
    {
        return;
    }
    //! 对话框里面的数据
    auto diaData = itemDialog->dialogMapData;
    auto krows = itemDialog->krows;
    auto vrows = itemDialog->vrows;
    if (krows == nullptr)
    {
        return;
    }
    //! 对话框标题：Data的节点
    QString k = itemDialog->windowTitle();
    //! 得到原来的节点
    auto oldPair = data->rootMap->value(k);
    auto oldKrows = oldPair->first;
    auto oldVrows = oldPair->second;
    QList<QList<QString>> newKrows;
    QList<QList<QString>> newVrows;
    int index = 0;
    for (auto r : oldKrows)
    {
        QList<QString>* rk = new QList<QString>;
        QList<QString>* rv = new QList<QString>;
        for (auto k : r) // k为英文
        {
            //rk->append(krows->at(index));// 翻译后的中文
            rk->append(k);// 翻译前的英文
            rv->append(vrows->at(index));
            index++;
        }
        newKrows.append(*rk);
        newVrows.append(*rv);
        rk = new QList<QString>;
        rv = new QList<QString>;
    }
    auto a = newKrows.size(); // 翻译后的中文
    auto b = oldKrows.size(); // 翻译前的英文

    QPair< QList<QList<QString>>, QList<QList<QString>>>* newPair = new QPair< QList<QList<QString>>, QList<QList<QString>>>;
    newPair->first = newKrows;
    newPair->second = newVrows;
    data->rootMap->insert(k, newPair);
}



void KFileEdtitor::treeViewClick()
{
    
    if (this->data == nullptr)
        return;

    //! 得到当前点击的键
    QTreeWidgetItem* item = treeWidget->treeItem->currentItem();
    QString item_text = item->text(0);
    if (item_text == u8"激活能量数值")return;

    QString parent_text;
    
    if (item->parent())
    {
        parent_text = item->parent()->text(0);
        if (parent_text == u8"激活能量数值" || item->text(0)=="" || item_text == u8"激活能量数值")
            return;

//     if (item->text(0) == u8"激活能量数值")
//         return;
        freshData();

        /* 创建数据模型 */
        QStandardItemModel* model = new QStandardItemModel();
        /* 设置表格标题行(输入数据为QStringList类型) */
        model->setHorizontalHeaderLabels({ u8"属性", u8"值" });
        model->setItem(0, 0, new QStandardItem(u8"名字"));
        model->setItem(0, 1, new QStandardItem(parent_text + "_" + item_text.mid(0, item_text.length() -5)));

        /* 设置表格视图数据 */
        treeWidget->itemAttr->setModel(model);
        treeWidget->itemAttr->verticalHeader()->hide();//不显示序号  

		auto a = parent_text + "_" + item->text(0);
        auto itemValue = data->rootMap->value(a);  // nullptr
		if (itemValue == nullptr)//|| valueOrder == nullptr
			return;
        //auto valueOrder = data->rootOrder->value(item->text(0));

        int index = data->rootOrder->indexOf(a);
        auto itemPair = data->rootMap->value(a);
        auto itemK = itemPair->first;
        auto itemv = itemPair->second;
		if (itemK.size() == 0)
			return;

        QList<QString> showK;
        for (auto row : itemK) {
            for (auto i : row) {
                showK.append(i);
            }
        }
        QList<QString> showV;
        for (auto row : itemv) {
            for (auto i : row) {
                showV.append(i);
            }
        }

        int lineCount = 1;
        for (int i = 0; i < showK.size(); i++)
        {
            if (showK[i].mid(0, 6) == "unused")
            {
                continue;
            }
            if (translator->json != nullptr)
            {
                QString lable_tr = translator->json->value(showK[i]).toString();
                if (lable_tr != "")
                {
                    model->setItem(lineCount, 0, new QStandardItem(showK[i] + "(" + lable_tr + ")"));
                    model->setItem(lineCount, 1, new QStandardItem(showV[i]));
                }
                else
                {
                    model->setItem(lineCount, 0, new QStandardItem(showK[i]));
                    model->setItem(lineCount, 1, new QStandardItem(showV[i]));
                }
            }
            else
            {
                model->setItem(lineCount, 0, new QStandardItem(showK[i]));
                model->setItem(lineCount, 1, new QStandardItem(showV[i]));
            }
            lineCount++;
        }
        auto notes = data->rootOrder_notes->at(index);
        model->setItem(lineCount, 0, new QStandardItem(notes));
        model->setItem(lineCount, 1, new QStandardItem());

        treeWidget->itemAttr->setSpan(lineCount, 0, 1, 2);
        /* 显示 */
        treeWidget->itemAttr->show();
    }
}

