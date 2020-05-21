#include "MessageProcess.h"
#include "MessageCache.h"
#include "InformationCache.h"
MessageProcess::MessageProcess(QObject* parent)
{
}

MessageProcess::~MessageProcess()
{
}

void MessageProcess::run()
{
	running = true;
	while (running)
	{
		auto& cache = Cache::get_instance();
		auto& info_cache = InformationCache::get_instance();
		auto msg = cache.get(Cache::STATUS_MESSAGE);
		std::string content;
		std::string app_name = "[" + msg.content.substr(0, msg.content.find("@")) + "]";
		std::string app_content = "[" + msg.content.substr(msg.content.find("@") + 1, std::string::npos) + "]";
		switch (msg.dwData)
		{
		case 0:
			content += app_name+status_str_.err+ app_content;
			emit running_error();
			break;
		case 1:
			content += app_name+status_str_.good + app_content;
			break;
		case 2:
			content += app_name + status_str_.done + app_content;
			break;
		default:
			break;
		}
		info_cache.insert(content);
	}
}
