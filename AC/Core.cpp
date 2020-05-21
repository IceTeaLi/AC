#include "Core.h"
#include "Process.h"
#include "Settings.h"
#include "MessageCache.h"
#include <stdexcept>
#include "MessageProcess.h"

Core::Core(QObject* parent)
	:QThread(parent)
{
	msg_processer = new MessageProcess(this);
	msg_processer->start();
}



void Core::run()
{
	auto scripts_dir = Settings::getInstance().get_scripts_folder()+"/";
	running = true;
	for (auto& name : list_)
	{
		if (running == false)
			break;
		Process process(scripts_dir + name.toStdString());
		process_ = &process;
		process.start();
		process.wait(3600000);
		process.stop();
	}
	process_ = nullptr;
}

void Core::stop()
{
	if (process_ != nullptr)
	{
		running = false;
		process_->stop();
	}
}

void Core::pause()
{
	if (process_ != nullptr)
	{
		process_->suspend(true);
	}
}

void Core::resume()
{
	if (process_ != nullptr)
	{
		process_->suspend(false);
	}
}

void Core::next()
{
	if (process_ != nullptr)
	{
		process_->stop();
	}
}

