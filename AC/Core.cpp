#include "Core.h"
#include "Process.h"
#include "Settings.h"
#include "MessageCache.h"
#include <stdexcept>
#include "MessageProcess.h"
#include "InformationCache.h"

Core::Core(QObject* parent)
	:QThread(parent)
{
	msg_processer = new MessageProcess(this);
	msg_processer->start();
}



void Core::run()
{
	auto scripts_dir = Settings::getInstance().get_scripts_folder()+"/";
	auto& info_cache = InformationCache::get_instance();
	running = true;
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
			info_cache.insert(CONTROLLER_TAG + ERROR_TAG	 + ":" + name.toStdString() + " : scripts start.");
			process.wait(3600000);
			process.stop();
		}
		catch (std::exception& e)
		{
			info_cache.insert(CONTROLLER_TAG + ERROR_TAG + std::string(e.what()));
		}

	}
	process_ = nullptr;
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

