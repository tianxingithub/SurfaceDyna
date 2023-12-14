#include "BTExternalProgramEditor.h"
#include "BTWindowMonitor.h"
#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QMetaType>
#include <QProcess>
#include <QTimer>
#include <QWindow>
#include <QApplication>

namespace BT
{
	BTExternalProgramEditor::BTExternalProgramEditor(const QString & cmd, const QString & working_directory, const QString & windowclass, const QString & windowtitle, QWidget *parent, bool autoLock)
		: Cmd(cmd), WorkingDirectory(working_directory), WindowClass(windowclass), WindowTitle(windowtitle), AutoLock(autoLock), QDialog(parent)
	{
// 		startExternalProgram();

		Hwnd = nullptr;
		IsLocked = true;
		IsMinimized = false;
		//setStyleSheet("QWidget{background-color:rgb(63,70,86);}");
		
	}

	BTExternalProgramEditor::BTExternalProgramEditor(HWND h, QWidget *parent)
		: QDialog(parent)
	{
		if(h)
			acceptWindowSlot(h);
	}

	BTExternalProgramEditor::~BTExternalProgramEditor()
	{

		if (Hwnd && IsWindow(Hwnd))
		{
			closeExternalProgram();
		}

		if (Monitor)
		{
			Monitor->destory();
			Monitor->wait();
		}
	}

	void BTExternalProgramEditor::startExternalProgram()
	{
		if (Hwnd && IsWindow(Hwnd))
			return;
		//! 创建窗口监视器，其运行机理是：在启动外部程序前，获取已知窗口类名、窗口标题的所有句柄，并通过计时器监测是否有新的窗口句柄产生
		Monitor = new BTWindowMonitor(WindowClass, WindowTitle, this);
		qRegisterMetaType<HWND>("HWND");
		connect(Monitor, SIGNAL(sendWindowSignal(HWND)), SLOT(acceptWindowSlot(HWND)));
		Monitor->start();
		//! 基于命令行启动外部程序
		QProcess *process = new QProcess(0);

		//这样起不来？
		/*process->setWorkingDirectory(WorkingDirectory);
		process->start(Cmd);*/
		
// 		process->setProgram(Cmd);
// 		process->start(QIODevice::Truncate);


		process->start(Cmd);
		process->waitForStarted();
		

	}

	void BTExternalProgramEditor::resizeEvent(QResizeEvent* event)
	{
		QWidget::resizeEvent(event);
		SetWindowPos(Hwnd, HWND_TOPMOST, 0, 0, this->width(), this->height(), SWP_NOACTIVATE | SWP_NOZORDER);
		//updateLocation();
	}

	bool BTExternalProgramEditor::killProcess(int pid)
	{
		HANDLE process = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
		DWORD status = TerminateProcess(process, 0);
		return (status == 0) ? 0 : 1;
	}

	void BTExternalProgramEditor::acceptWindowSlot(HWND h)
	{
		if (IsWindow(h))
		{
			Hwnd = h;
			Style = GetWindowLong(Hwnd, GWL_STYLE);

			if (AutoLock)
			{
				setLocked(true);
			}
		}

	}

	void BTExternalProgramEditor::closeExternalProgram()
	{
		DWORD pid;
		GetWindowThreadProcessId(Hwnd, &pid);
		killProcess(pid);
	}

	void BTExternalProgramEditor::updateLocation()
	{
		QPoint pos = mapToGlobal(QPoint(this->x(), this->y()));
		SetWindowPos(Hwnd, HWND_TOPMOST, pos.x(), pos.y(), this->width(), this->height(), SWP_NOACTIVATE | SWP_SHOWWINDOW);
	}

	void BTExternalProgramEditor::changeStatus(QEvent::Type type)
	{
		QPoint pos = mapToGlobal(QPoint(this->x(), this->y()));
		if (type == QEvent::WindowDeactivate)
		{
			SetWindowPos(Hwnd, HWND_NOTOPMOST, pos.x(), pos.y(), this->width(), this->height(), SWP_NOACTIVATE | SWP_SHOWWINDOW);
		}
		else if (type == QEvent::WindowActivate | type == QEvent::Move | type == QEvent::Show)
		{
			SetWindowPos(Hwnd, HWND_TOPMOST, pos.x(), pos.y(), this->width(), this->height(), SWP_NOACTIVATE | SWP_SHOWWINDOW);
		}
		else if (type == QEvent::Hide)
		{
			ShowWindow(Hwnd, SW_HIDE);
		}
		else if (type == QEvent::Close)
		{
			closeExternalProgram();
		}
	}

	void BTExternalProgramEditor::setLocked(bool locked)
	{
		setIsLocked(locked);
		if (locked)
		{

			SetParent(Hwnd, (HWND)this->winId());
			SetWindowPos(Hwnd, HWND_TOPMOST, 0, 0, this->width(), this->height(), SWP_NOACTIVATE | SWP_NOZORDER);
		}
		else
		{
			SetParent(Hwnd, NULL);
			auto sg = QApplication::desktop()->screenGeometry();
			MoveWindow(Hwnd, 0, 0, sg.width(), sg.height(), true);
		}
	}

	void BTExternalProgramEditor::setHwnd(HWND hwnd, bool close)
	{
		if (close)
		{
			closeExternalProgram();
		}
		Hwnd = hwnd;
		setLocked(true);
	}

	void BTExternalProgramEditor::minimizeWindow(bool isMini)
	{
		if (Hwnd)
		{
			if (isMini)
			{
				ShowWindow(Hwnd, SW_RESTORE);///<激活并显示窗口。如果窗口最小化或最大化，则系统将窗口恢复到原来的尺寸和位置。
			}
			else
			{
				ShowWindow(Hwnd, SW_MINIMIZE);///<最小化指定的窗口并且激活在Z序中的下一个顶层窗口。
			}
		}
	}
}