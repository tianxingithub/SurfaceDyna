#include "Data.h"

Data::Data()
{
	rootMap = new QMap<QString, QPair<QList<QList<QString>>, QList<QList<QString>>>*>;
	rootOrder = new QList<QString>;
	rootOrder_notes = new QList<QString>;
	rootList = new QList<QPair<QList<QList<QString>>, QList<QList<QString>>>*>;
	filename = "";
}

Data::~Data()
{
	//delete rootMap;
	//delete order;
}