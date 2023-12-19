#include "ReadThread.h"
#include "qfile.h"

ReadThread::ReadThread(QString f, QTextBrowser* d)
{
	filepath = f;
	display = d;
	data = nullptr;
	ready = false;
}

// 使用Unicode范围来判断字符是否为汉字
bool isChineseCharacter(const QChar& character)
{
	if (character == "" || character == " ")
		return false;
	return character >= 0x4e00 && character <= 0x9fff;
}

void ReadThread::run()
{	
	QFile file(filepath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return;
		//return nullptr;
	}
	Data*re = new Data();

	QTextStream in(&file);
	QString kItem=""; //! 上一个选项卡名字
	QString notes = " "; // !上一个选项卡的批注
	//! 节点的属性信息
	//! <每行属性，每行属性值>
	QPair<QList<QList<QString>>, QList<QList<QString>>>* itemPair = new QPair<QList<QList<QString>>, QList<QList<QString>>>;
	

	QList<QList<QString>>*k = nullptr;
	QList<QList<QString>>*v = nullptr;

	

	

	//! 每个节点的前缀起始
	int nodeStart = 1000;

	//! 按行读取文件
	bool isBreak = false;
	int rowCount = 0; // key文件的行号信息
	int browseLine = 0; // textBorwser的行号
	while (!in.atEnd())
	{
		if (isBreak)
		{
			break;
		}
		QByteArray line = file.readLine(); rowCount++;
		QString str(line);

		str.remove("\n");

		//! 判断选项卡
		if (str.at(0) == '*')
		{
			// 保存起来，导出的时候需要还原
			if (str == "*NODE" || str == "*ELEMENT_SOLID" || str == "*KEYWORD" || str == "*PARAMETER_DUPLICATION")//|| str == "*END"
			{


				continue;

			}
			if (kItem != "")
			{
// 				kItem = QString::number(nodeStart) + kItem; // 序号+节点 1000NT_SOLID
				kItem = kItem + "@"+ QString::number(nodeStart); // 节点+序号 NT_SOLID@1000
				itemPair->first = *k;
				itemPair->second = *v;
				re->rootList->append(itemPair);
				re->rootMap->insert(kItem, itemPair);
				notes.replace(" ", "");
				re->rootOrder_notes->append(notes);
				nodeStart++;
			}
			if (str == "*END")
			{
				isBreak = true;
				continue;
			}
			display->append(QString::number(rowCount) + "  " + str); browseLine++;

			itemPair = new QPair<QList<QList<QString>>, QList<QList<QString>>>;
			k = new QList<QList<QString>>;
			v = new QList<QList<QString>>;

			//! 添加树节点顺序
// 			re->rootOrder->append(QString::number(nodeStart) + str.mid(1));
			re->rootOrder->append(str.mid(1)+"@"+ QString::number(nodeStart));
			re->rootOrder_lines.append(browseLine);
			
			str = str.simplified();
			kItem = str.mid(1);		
			notes = " ";

		}//if
		//! 添加选项卡属性值
		else if (str.at(0) == '$')
		{
			if (str.size() == 1)
			{
				// 为"$"
				continue;
			}
			if (isChineseCharacter(str.at(1))) // 是批注
			{
				notes = notes + str.mid(1) +'\n';
				display->append(QString::number(rowCount) + "  " + str); browseLine++;
			}
			else if (str.at(1) == " ")
			{
				QList<QString>kk;
				QList<QString>vv;
				display->append(QString::number(rowCount) + "  " + str); browseLine++;

				str = str.simplified(); // ----------------------
				QStringList key = str.split(" "); // 下标1开始，最后一个为unused要丢弃

				int len = key.length();
				line = file.readLine(); rowCount++;// 属性的值 下标0开始

				QString strvalue(line);
				strvalue.remove("\n");
				display->append(QString::number(rowCount) + "  " + strvalue); browseLine++;
				strvalue = strvalue.simplified(); // ----------------------


				QStringList value = strvalue.split(" "); // 下标0开始

				for (int i = 0; i < len - 1; i++)
				{
					QT_TRY
					{
// 					qDebug() << key[i + 1];
						if (key[i + 1].mid(0, 6) == "unused")
						{
							kk.append(key[i + 1]);
							vv.append(" ");

						}
						else
						{
							if (i >= value.size())
							{
								kk.append(key[i + 1]);
								vv.append(" ");


							}
							else
							{
								kk.append(key[i + 1]);
								vv.append(value[i]);

							}

						}

					}
						QT_CATCH(const char* ex)
					{
						// 捕获并处理异常
						qDebug() << "Exception caught:" << ex;
					}
				}// for


				k->append(kk);
				v->append(vv);


			}//else if 	
		}
	}//end while

	display->append(" ");
	ready = true;
	this->data = re;

	file.close();
}