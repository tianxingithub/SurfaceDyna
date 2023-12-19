#include "ReadWrite.h"
#include "QFile"
#include "qtextstream.h"
#include "qtextbrowser.h"
#include "QDebug"
#include "ReadThread.h"
#include "ReadThread.h"
#include "KFileEdtitor.h"
#include <QMessageBox>


ReadWrite::ReadWrite()
{
	
}

ReadWrite::~ReadWrite()
{

}

void ReadWrite::readData(QString filepath, QTextBrowser* display)
{
	readthread = new ReadThread(filepath, display);
	readthread->run();  finishedSlot();
// 	readthread->start();

	connect(readthread, &QThread::finished, this, &ReadWrite::finishedSlot);

}

void ReadWrite::writeDataRoot(QString filepath, Data* data)
{
	QFile f(filepath);
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << u8"打开文件失败";
		return;
	}
	QTextStream txtOutput(&f);
	txtOutput.setCodec("UTF-8");

	// 写入导出信息
	QString titleInfo = u8"$# 激发仿真软件研发支撑服务平台导出k文件信息";
	txtOutput << titleInfo << endl;


	//! 树节点顺序
	auto node1 = data->rootOrder;

	//! 节点对应的批注
	auto notes = data->rootOrder_notes;
	
	//! 开始遍历树节点
	for (auto n1 : *node1)
	{
		auto n = n1.mid(0, n1.length() - 5);
		txtOutput << "*"+n1.mid(0,n1.length()-5) << endl;
		
		// 写入节点批注
		auto item_index = data->rootOrder->indexOf(n1);
		auto notes = (*data->rootOrder_notes)[item_index];

		notes.replace(" ", "");
		notes.replace('\n', "\n$");
		if (notes != "")
		{
			txtOutput << "$" << notes << endl;

		}

		//! 节点的QPair
		auto kvpair = data->rootMap->value(n1);
		auto krows = kvpair->first;
		auto vrows = kvpair->second;
		if (krows.size() == 0)
		{
			qDebug() << "krows.size() = 0";
			return;
		}
			
		int rcount = 0;
		for (auto row : krows)
		{
			int kcount = row.size();
			int space = kcount <= 8 ? 10 : 80 / kcount;
			int count = 0;
			for (auto k : row)
			{
				if (count == 0)
				{
					txtOutput << "$"<< k.rightJustified(space - 1, ' ');
					count++;
				}
				else
				{
					if (k.mid(0, 6) == "unused")
					{
						txtOutput << k.rightJustified((8-count)*10, ' ');
					}
					else
					{
						txtOutput << k.rightJustified(space, ' ');
						count++;
					}						
				}
			}
			txtOutput << endl;
			count = 0;
			for (int i = 0; i < row.size(); i++)
			{
				if (krows[rcount][i] == "unused")
				{
					txtOutput <<  vrows[rcount][i].rightJustified((8 - count) * 10, ' ');
				}
				else
				{
					txtOutput << vrows[rcount][i].rightJustified(space, ' ');
					count++;
				}					
			}
			txtOutput << endl;
			rcount++;
		}
	}


	txtOutput << "*END" << endl;

	f.close();

	QString msg = u8"文件已导出至 "+filepath;
	QMessageBox::information(new QDialog, u8"导出完成", msg, QMessageBox::Ok);
}

void ReadWrite::writeData(QString filepath, Data* data)
{
	QFile ofile(filepath);
	if (!ofile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << u8"创建文件失败";
		return;
	}
	QFile ifile(filepath);
	if (!ifile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << u8"导出时读取原始文件失败";
		return;
	}

	QTextStream in(&ifile);
	while (!in.atEnd()) //! 按行读取文件
	{
		QByteArray line = ifile.readLine(); 
		QString str(line);
		if (str.at(0) == '*')
		{
			if (str == "*NODE" || str == "*ELEMENT_SOLID" || str == "*KEYWORD" || str == "*PARAMETER_DUPLICATION" || str == "*END")
			{
				// 把读取的写进输出文件

			}			
		}
	}
	
	ofile.close();
	ifile.close();
}

void ReadWrite::testSlots()
{
	auto obj = dynamic_cast<ReadThread*>(sender());
	if (obj)
	{
		auto re = obj->data;
	}
	
	
	qDebug() << "*****************ReadWrite::testSlots*************";
}

void ReadWrite::finishedSlot()
{
	int i = 1;
	Data* re = readthread->data;
	emit readFinishedSig(re);
}
