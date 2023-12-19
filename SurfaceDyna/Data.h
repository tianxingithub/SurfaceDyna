#pragma once
#include <QString>
#include "QMap"

//! ���ڵ�ļ�ֵ��������ֵ
class Data
{
public:
	Data();
	~Data();
public:


	//! ���ڵ�ļ�ֵ
	QMap<QString, QPair<QList<QList<QString>>, QList<QList<QString>>>*>* rootMap;
	
	//! ���ڵ������ֵ
	QList< QPair<QList<QList<QString>>, QList<QList<QString>>>*>* rootList;

	//! ���ڵ��˳��
	QList<QString>* rootOrder;
	
	//! ���ڵ��Ӧ����ע
	QList<QString>* rootOrder_notes;

	//! ���ڵ���TextBrowser�ж�Ӧ���к�
	QList<int> rootOrder_lines;

	//! �򿪵��ļ�����
	QString filename;

private:
	//! ��ȡ�������ļ�����
	 QStringList m_fileLines;

public:
	void setfileLines(const QStringList  fL) { m_fileLines = fL; }
	QStringList  getfileLines() const { return m_fileLines; }


public:
	//<QString, QMap<QString, QString >*>* getRootMap
};

