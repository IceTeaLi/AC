#include "Server.h"
#include "MessageCache.h"
#include <Windows.h>
Server::Server(QWidget* parent)
	:QDialog(parent)
{
	this->setWindowTitle(QString("ipc-server"));
//	this->setWindowFlag(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowOpacity(0);
	this->show();
}

bool Server::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	if (eventType == "windows_generic_MSG")
	{
		PMSG msg = static_cast<PMSG>(message);
		if (msg->message == WM_COPYDATA)
		{
			auto& cache = Cache::get_instance();
			PCOPYDATASTRUCT temp = reinterpret_cast<PCOPYDATASTRUCT>(msg->lParam);
			MyMessage my_msg = { temp->dwData,reinterpret_cast<char*>(temp->lpData) };
			cache.insert(my_msg, msg->wParam);
		}
	}
	return false;
}
