#include "BTWindowMonitor.h"

namespace BT
{
	BTWindowMonitor::BTWindowMonitor(QObject *parent)
		: QThread(parent)
	{
		IsRunning = false;
		CurrentHwnd = nullptr;
	}

	BTWindowMonitor::BTWindowMonitor(const QString & window_class, const QString & window_title, QObject *parent)
		: WindowClass(window_class), WindowTitle(window_title), QThread(parent)
	{
		IsRunning = false;
		CurrentHwnd = nullptr;

		HWND hwnd{ NULL };
		while (1)
		{
			hwnd = findHwnd(hwnd);
			if (hwnd)
			{
				PrimaryHwnds.append(hwnd);
				continue;
			}
			else
			{
				break;
			}
		}
	}

	BTWindowMonitor::~BTWindowMonitor()
	{
	}

	void BTWindowMonitor::destory()
	{
		IsRunning = false;
	}

	void BTWindowMonitor::run()
	{
		IsRunning = true;

		while (1)
		{
			if (IsRunning)
			{
				HWND hwnd{ NULL };
				QList<HWND> m_current_hwnds;
				while (1)
				{
					hwnd = findHwnd(hwnd);
					if (hwnd)
					{
						m_current_hwnds.append(hwnd);
						continue;
					}
					else
					{
						break;
					}
				}
				//! 判别是否存在新的窗口
				for (const auto & iter : m_current_hwnds)
				{
					if (!PrimaryHwnds.contains(iter))
					{
						if (IsWindow(iter))
						{
							sendWindowSignal(iter);
							IsRunning = false;
							return;
						}
					}
				}
			}
			else
			{
				return;
			}
		}
	}

	HWND BTWindowMonitor::findHwnd(HWND h)
	{
		if ("" == WindowClass | NULL == WindowClass)
		{
			return FindWindowEx(NULL, h, NULL, WindowTitle.toStdWString().c_str());
		}
		else
		{
			return FindWindowEx(NULL, h, WindowClass.toStdWString().c_str(), WindowTitle.toStdWString().c_str());
		}
		return nullptr;
	}
}