#include "KFileEdtitor.h"
#include "KDyna.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//     KFileEdtitor w;
    KDyna w2;

	QIcon icon("./images/logo.ico");
	a.setWindowIcon(icon);

	QString qssFile = QString("./qss/kdyna-style.css");
	QFile styleFile(qssFile);
	if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream styleStream(&styleFile);
		QString style = styleStream.readAll();
		w2.setStyleSheet(style);
		styleFile.close();
	}
//     w.show();
    w2.show();
    return a.exec();
}
