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
	DBManager database_manager("results_process");
	running = true;
	while (running)
	{
		auto results = cache.get(Cache::RESULTS_MESSAGE);
		QString results_qstr = QString::fromStdString(results.content);
		QString application_name = results_qstr.section("@", 0, 0);
		QString test_item_name = results_qstr.section("@", 1, 1);
		QString data = results_qstr.section("@", 2, 2);
		try
		{
			database_manager.insert(application_name, test_item_name, data);
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
	database_manager.close();
}
