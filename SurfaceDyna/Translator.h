#pragma once
#include "QMap"
#include "QString"
#include <QJsonDocument>
#include <QJsonObject>
#include "QFile"
#include "QIODevice"
#include "QDebug"
//! �ı�����
class Translator : public QObject
{
	//Q_OBJECT
public:
	//! �洢��������
	QJsonObject* json;
	//! �����ļ�·��
	QString filepath;

public:
	Translator(QString filepath = "");

private:
	//! ��ȡ�����ļ�
	QJsonObject* readJson();

public slots: //slots��Ҫ�ɲ�Ҫ
	void testSlots();
	
};

