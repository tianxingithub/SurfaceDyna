#pragma once

#include <QThread>
#include <QList>

#include "windows.h"
#include "CoreGlobal.h"

namespace BT
{
	class  BTWindowMonitor : public QThread
	{
		Q_OBJECT
		DefineNonpointerMember(bool,		IsRunning)
		DefineNonpointerMember(QString,		WindowClass)
		DefineNonpointerMember(QString,		WindowTitle)
		DefineNonpointerMember(QList<HWND>, PrimaryHwnds)
		DefineNonpointerMember(HWND,		CurrentHwnd)

	public:
		BTWindowMonitor(QObject *parent);
		BTWindowMonitor(const QString & window_class, const QString & window_title, QObject *parent);
		~BTWindowMonitor();

		void run();
		void destory();

	signals:
		void sendWindowSignal(HWND h);

	private:
		HWND findHwnd(HWND h);
	};
}