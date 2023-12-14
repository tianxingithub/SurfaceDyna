#pragma once

#include <QDialog>
#include <QTimer>
#include <QEvent>

#include "windows.h"
#include "CoreGlobal.h"
// #include <QProcess>

namespace BT
{
	
	class BTWindowMonitor;
	//! 该窗口类用于集成外部程序界面，输入执行命令行、窗口类名、窗口标题名
	class  BTExternalProgramEditor : public QDialog
	{
		Q_OBJECT
		DefineNonpointerMember(QString, Cmd)
		DefineNonpointerMember(QString, WorkingDirectory)
		DefineNonpointerMember(QString, WindowClass)
		DefineNonpointerMember(QString, WindowTitle)
		DefineNonpointerMember(bool,	AutoLock)
		DefineNonpointerMember(bool,	IsLocked)
		DefineNonpointerMember(bool,	IsMinimized)
		DefineNonpointerMember(HWND,	Hwnd)
		DefineNonpointerMember(LONG,	Style)
		DefinePointerMember(BTWindowMonitor, Monitor)

	public:
		BTExternalProgramEditor(const QString & cmd, const QString & working_directory, const QString & windowclass
			, const QString & windowtitle, QWidget *parent = Q_NULLPTR, bool autoLock = true);

		BTExternalProgramEditor(HWND h, QWidget *parent);

		~BTExternalProgramEditor();

		void startExternalProgram();

		void closeExternalProgram();

		void changeStatus(QEvent::Type type);

		void setLocked(bool locked);

		void setHwnd(HWND hwnd, bool close = false);

		void minimizeWindow(bool isMini);

// 		Q_PID m_wid;
	public:
		void resizeEvent(QResizeEvent* event);

	private:
		//! 关闭指定ID进程
		bool killProcess(int pid);
		//! 安装事件过滤器
		void filter(QObject* parent);
		//! 更新位置
		void updateLocation();

		private slots:
		void acceptWindowSlot(HWND h);
	};
}