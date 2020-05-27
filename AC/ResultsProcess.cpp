#include "ResultsProcess.h"
#include "MessageCache.h"
#include "InformationCache.h"
#include "DBManager.h"
#include <QString>
#include <QDebug>
ResultsProcess::ResultsProcess(QObject* parent)
	:QThread(parent)
{

}

ResultsProcess::~ResultsProcess()
{
	this->running = false;
	this->wait();
}

void ResultsProcess::run()
{
	auto& cache = Cache::get_instance();
	auto& info_cache = InformationCache::get_instance();
	auto& database = DBManager::get_instance();
	running = true;
	while (running)
	{
		auto results = cache.get(Cache::RESULTS_MESSAGE);
		QString application_name = QString::fromStdString(results.content.substr(0, results.content.find_first_of("@")));
		QString test_item_name = QString::fromStdString(results.content.substr(results.content.find_first_of("@") + 1, results.content.rfind(":@")- results.content.find_first_of("@")));
		QString data = QString::fromStdString(results.content.substr(results.content.find_last_of("@") + 1, std::string::npos));
		try
		{
			database.insert(application_name, test_item_name, data);
		}
		catch (std::exception& e)
		{
			info_cache.insert(CONTROLLER_TAG + ERROR_TAG + e.what());
		}
		
		info_cache.insert("[" + application_name.toStdString() + "]"
			+ "[RESULT]"
			+ test_item_name.toStdString() + ": "
			+ data.toStdString()
		);
	}
	qDebug() << "message process exit";
}
