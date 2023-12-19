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
#include <QMessageBox>


KFileEdtitor::KFileEdtitor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::KFileEdtitorClass())
{
    ui->setupUi(this);
    setBtnsSize();


	m_fileRW = new ReadWrite();
	m_data = nullptr;
	m_itemDialog = nullptr;
    m_settingDialg = nullptr;
    m_settingDialg = new SettingDialog(this);

    m_treeWidget = new TreeWidget(ui->centralWidget);
    m_treeWidget->setMinimumSize(250, 600);
    ui->verticalLayout->addWidget(m_treeWidget);

    m_displayWidget = new DisplayWidget(ui->centralWidget);
    m_displayWidget->setMinimumSize(600, 500);
	ui->horizontalLayout_4->addWidget(m_displayWidget);

    m_translator = nullptr;
    auto tsPath = m_settingDialg->m_TsPath;
    m_translator = new Translator(tsPath);

    addPlot();
}

KFileEdtitor::~KFileEdtitor()
{
    delete ui;
}

void KFileEdtitor::addPlot()
{
	connect(ui->btnOpen, &QPushButton::clicked, this, &KFileEdtitor::getData);
	connect(ui->btnSave, &QPushButton::clicked, this, &KFileEdtitor::exportData);
	connect(ui->btnSetting, &QPushButton::clicked, this, &KFileEdtitor::settingSlot);
	connect(ui->btnOpenDyna, &QPushButton::clicked, this, &KFileEdtitor::openDynaSlot);

//     connect(ui->actionOpen, &QAction::triggered, this, &KFileEdtitor::getData);
//     connect(ui->actionSave, &QAction::triggered, this, &KFileEdtitor::exportData);
// 	connect(ui->actionSetting, &QAction::triggered, this, &KFileEdtitor::settingSlot);
// 	connect(ui->actionOpenDyna, &QAction::triggered, this, &KFileEdtitor::openDynaSlot);
// 	connect(ui->actionDynaClose, &QAction::triggered, this, &KFileEdtitor::closeDynaSlot);

	connect(m_fileRW, &ReadWrite::readFinishedSig, this, &KFileEdtitor::readOverSlot);
    connect(m_treeWidget->treeItem, &QTreeWidget::doubleClicked, this, &KFileEdtitor::treeViewDoubleClickSlot);
    connect(m_treeWidget->treeItem, &QTreeWidget::clicked, this, &KFileEdtitor::treeViewClickSlot);

    //connect(ui->menuSlot, &QMenu::triggered, this, &KFileEdtitor::menuTestSlot);
}

void KFileEdtitor::setBtnsSize()
{
    ui->btnOpen->setFixedSize(32, 32);
    ui->btnOpen->setIcon(QIcon(("./images/open-kdyna.ico")));


    ui->btnSave->setFixedSize(32, 32);
    ui->btnSave->setIcon(QIcon("./images/export-kdyna.ico"));

    ui->btnSetting->setFixedSize(32, 32);
    ui->btnSetting->setIcon(QIcon("./images/setting-kdyna.ico"));

    ui->btnOpenDyna->setFixedSize(32, 32);
    ui->btnOpenDyna->setIcon(QIcon("./images/dyna.ico"));
}

void KFileEdtitor::funDemoSlot()
{
    QMap<QString, QMap<QString, QString>>m;
    m.insert(QString("a"), QMap<QString, QString>());
    auto mm = m["b"];


}

void KFileEdtitor::getData()
{
    QString filepath = QFileDialog::getOpenFileName(// ��������
        this, u8"��K�ļ�",
        ".",
        "k files (*.k);;All files (*.*)");
    if (filepath == nullptr)
        return;

    if (m_data)
    {
        delete m_data;
        m_data = nullptr;
        m_displayWidget->textDisplay->clear();
        m_treeWidget->treeItem->clear();
        m_treeWidget->initTree();
        m_parentNodes = QHash<QString, QTreeWidgetItem*>();
    }
    
    /*this->data = */m_fileRW->readData(filepath, m_displayWidget->textDisplay);
//     displayItem();
}

void KFileEdtitor::exportData()
{
	auto obj = dynamic_cast<ReadThread*>(sender());
	if (obj)
	{
		this->m_data = obj->data;
	}
    if (m_data == nullptr)
    {
        QMessageBox::information(this, u8"����", u8"δ���ļ���");
		return;
    }
    QString filepath = QFileDialog::getSaveFileName(this, u8"����K�ļ�",
        ".",
        "k files (*.k);;all files(*.*)");
    m_fileRW->writeDataRoot(filepath,m_data);

}

void KFileEdtitor::displayItem()
{
    if (m_data == nullptr)
        return;
    m_treeWidget->treeItem->setRootIsDecorated(false);
    auto parent_nodes = m_data->rootOrder;

    foreach (auto s , *(m_data->rootOrder))
    {
        auto a = m_data->rootMap->value(s);
        if (a==nullptr)
            continue;
        QStringList parts = s.split("_");
        QString parentName = parts[0]; // ��ȡ���ڵ�����

		// ��鸸�ڵ��Ƿ��Ѵ��ڣ�����������򴴽�
        if (!m_parentNodes.contains(parentName))
        {
            QTreeWidgetItem* parentNode = new QTreeWidgetItem(m_treeWidget->root);
            parentNode->setText(0, parentName);
            parentNode->setIcon(0, QIcon("./images/fir.png"));
            m_parentNodes[parentName] = parentNode;
        }

        QTreeWidgetItem* childItem1 = new QTreeWidgetItem(m_parentNodes[parentName]);
        childItem1->setIcon(0, QIcon("./images/sec.png"));
        childItem1->setText(0, s.mid(parentName.size()+1));
    }
    m_treeWidget->treeItem->expandAll();  // չ�����нڵ�
    m_treeWidget->treeItem->sortItems(0, Qt::AscendingOrder);
}

void KFileEdtitor::readOverSlot(Data*re)
{
    int a = 1;
	
    this->m_data = re;
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
			// ��ȡ���嵱ǰ��ʽ
			LONG style = GetWindowLong(hwnd, GWL_STYLE);

			// ��󻯴���
			ShowWindow(hwnd, SW_MAXIMIZE);

			// ���ر�����
			SetWindowLong(hwnd, GWL_STYLE, style & ~WS_CAPTION);

			// ʹ�ı���Ч
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
        
        m_dyna->closeExternalProgram();
		m_dyna = NULL;
    }

}


void KFileEdtitor::menuTestSlot()
{
    qDebug() << "menuSlot()";
}

void KFileEdtitor::treeViewDoubleClickSlot()
{
	if (this->m_data == nullptr)
		return;

	QTreeWidgetItem* item = m_treeWidget->treeItem->currentItem();
	QString item_text = item->text(0);

	if (item_text == u8"����������ֵ") return;

	QString key = item->text(0);
    QString parent_text;
    
    if (item->parent())
    {
        parent_text = item->parent()->text(0);
        if (parent_text == u8"����������ֵ" || item->text(0) == "" || item_text == u8"����������ֵ")
            return;

        // 	if (key == u8"����������ֵ") return;
        key = parent_text +"_" + key;

        if (m_itemDialog)
        {
            delete m_itemDialog;
            m_itemDialog = NULL;
        }
        m_itemDialog = new ItemDialog(this);
        //(parent_text + "_" + item_text.mid(0, item_text.length() -5)));
//         itemDialog->setWindowTitle(parent_text + "_" + item_text.mid(0, item_text.length() - 5));
        m_itemDialog->setWindowTitle(key);
        connect(m_itemDialog, &ItemDialog::doubleClickSig, this, &KFileEdtitor::treeViewClickSlot);

        auto kvPair = m_data->rootMap->value(key);
        auto item_index = m_data->rootOrder->indexOf(key);
        auto item_notes = m_data->rootOrder_notes->at(item_index);
        qDebug() << "--------------------------" << item_notes;
        auto kRow = kvPair->first;
        auto vRow = kvPair->second;

        if (kRow.size() == 0)
        {
            qDebug() << "���ݳ���k.size()=0,������ֵ";
            return;
        }
        int w = 90, h = 30, px = 10, py = 40;
        int numCount = 0;
        int rowCount = 0;

        int py_tr_v = 0;
        int py_tr_k = 0;
        for (auto row : kRow)//������һ�е�����
        {
            for (int i = 0; i < row.size(); i++)
            {
                auto k = row[i];
                int kcount = kRow.last().size() <= 8 ? 8 : kRow.last().size();

                QLabel* label = new QLabel(m_itemDialog);
                QLabel* label_tr = new QLabel(m_itemDialog);
                py_tr_v = (rowCount + 1) * (h - 16);
                if (rowCount == 0)
                {
                    py_tr_k = rowCount * h;
                }
                else
                {
                    py_tr_k = rowCount * (h - 16);
                }
                //! ��������
                if (m_translator->json != nullptr)
                {
                    QString jLable = m_translator->json->value(k).toString();
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

                // ���Lable��unusedֱ�ӷ��������
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


                //! ��unused���Ե�ֵ����Ϊ�����޸ĵ�textBrowser
                if (k.mid(0, 6) == "unused")
                {
                    QLineEdit* value = new QLineEdit(m_itemDialog);
                    value->setReadOnly(true); // ����Ϊֻ��
                    value->setText(vRow[rowCount][i]);
                    value->setAlignment(Qt::AlignCenter);
                    value->setGeometry((w + px) * (kcount - 1) + 45, (h + py) * rowCount + py_tr_v + 35, w, h);
                }
                else
                {
                    QLineEdit* value = new QLineEdit(m_itemDialog);
                    value->setText(vRow[rowCount][i]);
                    value->setGeometry((w + px) * i + 45, (h + py) * rowCount + py_tr_v + 35, w, h);
                }

            }
            rowCount++;
        }

        int xcount = kRow.last().size() <= 8 ? 8 : kRow.last().size();

        int xx = (w + px) * (xcount + 1) - 20;
        int yy = (h + py) * (kRow.size() + 1) + 50 + py_tr_v;

        // ��ʾ�ڵ���ע
        if (item_notes != " ")
        {
            yy += 30;
			QTextEdit* textBro_notes = new QTextEdit(m_itemDialog); //item_notes
			textBro_notes->setGeometry(45, yy - 140, 790, 80); // ���� QTextBrowser ��λ�úʹ�С
			textBro_notes->setPlainText(item_notes);            
        }
        else
        {
            //yy -= 60;
			yy += 30;
			QTextEdit* textBro_notes = new QTextEdit(m_itemDialog); //item_notes
			textBro_notes->setGeometry(45, yy - 140, 790, 80); // ���� QTextBrowser ��λ�úʹ�С
        }

        m_itemDialog->resize(xx, yy);
        m_itemDialog->setFixedSize(xx, yy);
        m_itemDialog->m_save->move(xx - 235, yy - 45);
        m_itemDialog->m_save->resize(w, h);
        m_itemDialog->m_save->setVisible(true);
        m_itemDialog->m_cacel->move(xx - 135, yy - 45);
        m_itemDialog->m_cacel->resize(w, h);
        m_itemDialog->m_cacel->setVisible(true);

        m_itemDialog->show();
    }
}


void KFileEdtitor::freshData()
{
    if (m_data == nullptr)
        return;

    if (m_itemDialog == nullptr)
    {
        return;
    }

    //! �Ի������������
    auto diaData = m_itemDialog->m_dialogMapData;
    auto krows = m_itemDialog->m_krows;
    auto vrows = m_itemDialog->m_vrows;
    auto notes = m_itemDialog->m_notes;
    if (krows == nullptr)
    {
        return;
    }
    //! �Ի�����⣺Data�Ľڵ�
    QString k = m_itemDialog->windowTitle();
    //! �õ�ԭ���Ľڵ�
    auto oldPair = m_data->rootMap->value(k);
    auto oldKrows = oldPair->first;
    auto oldVrows = oldPair->second;
    QList<QList<QString>> newKrows;
    QList<QList<QString>> newVrows;
    int index = 0;
    for (auto r : oldKrows)
    {
        QList<QString>* rk = new QList<QString>;
        QList<QString>* rv = new QList<QString>;
        for (auto k : r) // kΪӢ��
        {
            //rk->append(krows->at(index));// ����������
            rk->append(k);// ����ǰ��Ӣ��
            rv->append(vrows->at(index));
            index++;
        }
        newKrows.append(*rk);
        newVrows.append(*rv);
        rk = new QList<QString>;
        rv = new QList<QString>;
    }

    auto a = newKrows.size(); // ����������
    auto b = oldKrows.size(); // ����ǰ��Ӣ��

    QPair< QList<QList<QString>>, QList<QList<QString>>>* newPair = new QPair< QList<QList<QString>>, QList<QList<QString>>>;
    newPair->first = newKrows;
    newPair->second = newVrows;
    m_data->rootMap->insert(k, newPair);

    // �õ�k���������ѵ�ǰ������Ϣ����ע��ֵ
	auto item_index = m_data->rootOrder->indexOf(k);
    auto item_notes = (*m_data->rootOrder_notes)[item_index]=notes;

}



void KFileEdtitor::treeViewClickSlot()
{
    
    if (this->m_data == nullptr)
        return;

    //! �õ���ǰ����ļ�
    QTreeWidgetItem* item = m_treeWidget->treeItem->currentItem();
    QString item_text = item->text(0);
    if (item_text == u8"����������ֵ")return;

    QString parent_text;
    
    if (item->parent())
    {
        parent_text = item->parent()->text(0);
        if (parent_text == u8"����������ֵ" || item->text(0)=="" || item_text == u8"����������ֵ")
            return;

//     if (item->text(0) == u8"����������ֵ")
//         return;
        freshData();

        /* ��������ģ�� */
        QStandardItemModel* model = new QStandardItemModel();
        /* ���ñ�������(��������ΪQStringList����) */
        model->setHorizontalHeaderLabels({ u8"����", u8"ֵ" });
        model->setItem(0, 0, new QStandardItem(u8"����"));
        model->setItem(0, 1, new QStandardItem(parent_text + "_" + item_text.mid(0, item_text.length() -5)));

        /* ���ñ����ͼ���� */
        m_treeWidget->itemAttr->setModel(model);
        m_treeWidget->itemAttr->verticalHeader()->hide();//����ʾ���  

		auto a = parent_text + "_" + item->text(0);
        auto itemValue = m_data->rootMap->value(a);  // nullptr
		if (itemValue == nullptr)//|| valueOrder == nullptr
			return;
        //auto valueOrder = data->rootOrder->value(item->text(0));

        int index = m_data->rootOrder->indexOf(a);
        auto itemPair = m_data->rootMap->value(a);
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
            if (m_translator->json != nullptr)
            {
                QString lable_tr = m_translator->json->value(showK[i]).toString();
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
        auto notes = m_data->rootOrder_notes->at(index);
        model->setItem(lineCount, 0, new QStandardItem(notes));
        model->setItem(lineCount, 1, new QStandardItem());

        m_treeWidget->itemAttr->setSpan(lineCount, 0, 1, 2);
        /* ��ʾ */
        m_treeWidget->itemAttr->show();
    }
}

