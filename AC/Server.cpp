#include "Server.h"
#include "MessageCache.h"
#include <Windows.h>

Server::Server(QWidget* parent)
	:QWidget(parent)
{
	this->setWindowTitle(QString("ipc-server"));
}

bool Server::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	if (eventType == "windows_generic_MSG")
	{
		PMSG msg = static_cast<PMSG>(message);
		if (msg->message == WM_COPYDATA)
		{
			auto& cache = Cache::get_instance();
			std::string temp = reinterpret_cast<char*>(msg->lParam);
			cache.insert(temp, msg->wParam);
		}
	}
	return false;
}
