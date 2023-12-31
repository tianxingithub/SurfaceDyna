#pragma once
#include <QString>
#include "QMap"

//! 树节点的键值和其属性值
class Data
{
public:
	Data();
	~Data();
public:


	//! 树节点的键值
	QMap<QString, QPair<QList<QList<QString>>, QList<QList<QString>>>*>* rootMap;
	
	//! 树节点的属性值
	QList< QPair<QList<QList<QString>>, QList<QList<QString>>>*>* rootList;

	//! 树节点的顺序
	QList<QString>* rootOrder;
	
	//! 树节点对应的批注
	QList<QString>* rootOrder_notes;

	//! 树节点在TextBrowser中对应的行号
	QList<int> rootOrder_lines;

	//! 打开的文件名称
	QString filename;

private:
	//! 读取的完整文件数据
	 QStringList m_fileLines;

public:
	void setfileLines(const QStringList  fL) { m_fileLines = fL; }
	QStringList  getfileLines() const { return m_fileLines; }


public:
	//<QString, QMap<QString, QString >*>* getRootMap
};

