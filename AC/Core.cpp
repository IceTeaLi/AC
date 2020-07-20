#include "Core.h"
#include "Process.h"
#include "Settings.h"
#include "MessageCache.h"
#include "MessageProcess.h"
#include "ResultsProcess.h"
#include "InformationCache.h"
#include "DBManager.h"

#include <stdexcept>
#include <time.h>
Core::Core(QObject* parent)
	:QThread(parent)
{
	msg_processer = new MessageProcess(this);
	msg_processer->start();
	result_processer = new ResultsProcess(this);
	result_processer->start();
}

Core::~Core()
{
	msg_processer->stop();
	if (!msg_processer->wait(100))
		msg_processer->terminate();
	delete msg_processer;
	result_processer->stop();
	if (!result_processer->wait(100))
		result_processer->terminate();
	delete result_processer;
}

void Core::run()
{
	auto scripts_dir = Settings::getInstance().get_scripts_folder()+"/";
	auto& info_cache = InformationCache::get_instance();

	running = true;

	DBManager database_manager("core");
	time_t sys_time;
	time(&sys_time);
	auto convert_sys_time = localtime(&sys_time);
	std::string title = "["
		+std::to_string(convert_sys_time->tm_year+1900)+"/"
		+ std::to_string(convert_sys_time->tm_mon+1) + "/"
		+ std::to_string(convert_sys_time->tm_mday) + "-"
		+ std::to_string(convert_sys_time->tm_hour) + ":"
		+ std::to_string(convert_sys_time->tm_min) + ":"
		+ std::to_string(convert_sys_time->tm_sec)
		+ "]";
	database_manager.set_table(QString::fromStdString(title));
	database_manager.init_table();

	for (auto& name : list_)
	{
		if (running == false)
			break;
		Process process(scripts_dir + name.toStdString());
		process_ = &process;
		current_scripts_ = name;
		try
		{
			process.start();
			info_cache.insert(CONTROLLER_TAG + GOOD_TAG	 + ":" + name.toStdString() + ":scripts start.");
			process.wait(3600000);
			process.stop();
		}
		catch (std::exception& e)
		{
			info_cache.insert(CONTROLLER_TAG + ERROR_TAG + std::string(e.what()));
		}

	}
	process_ = nullptr;
	emit emit_test_over(QString::fromStdString(title));
	database_manager.close();
}

void Core::stop()
{
	if (process_ != nullptr)
	{
		auto& info_cache = InformationCache::get_instance();
		running = false;
		process_->stop();
		info_cache.insert(CONTROLLER_TAG + WARN_TAG + ":" + current_scripts_.toStdString() + " : force stop the test project");
	}
}

void Core::pause()
{
	if (process_ != nullptr)
	{
		auto& info_cache = InformationCache::get_instance();
		process_->suspend(true);
		info_cache.insert(CONTROLLER_TAG + GOOD_TAG + ":" + current_scripts_.toStdString() + " : script paused.");
	}
}

void Core::resume()
{
	if (process_ != nullptr)
	{
		auto& info_cache = InformationCache::get_instance();
		process_->suspend(false);
		info_cache.insert(CONTROLLER_TAG + GOOD_TAG + ":" + current_scripts_.toStdString() + " : script resumed.");
	}
}

void Core::next()
{
	if (process_ != nullptr)
	{
		auto& info_cache = InformationCache::get_instance();
		process_->stop();
		info_cache.insert(CONTROLLER_TAG + WARN_TAG + ":" + current_scripts_.toStdString() + " : force switch to next script.");
	}
}

